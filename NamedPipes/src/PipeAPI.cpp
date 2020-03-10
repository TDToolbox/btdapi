#include "pch.hpp"
#include "PipeAPI.hpp"
#include "Config.hpp"
#include "g3log/g3log.hpp"
#include <thread>

namespace PipeAPI {

Pipe::Pipe(std::wstring PipeName) { m_pipeName = L"\\\\.\\pipe\\" + PipeName; }

void Pipe::CreatePipe()
{
    m_pipeHandle = CreateNamedPipeW(
        m_pipeName.c_str(), PIPE_ACCESS_DUPLEX,
        PIPE_TYPE_BYTE | PIPE_WAIT | PIPE_REJECT_REMOTE_CLIENTS,
        PIPE_UNLIMITED_INSTANCES, PipeBufferSize, PipeBufferSize,
        NMPWAIT_USE_DEFAULT_WAIT, NULL);

    if (m_pipeHandle == INVALID_HANDLE_VALUE) {
        auto error = GetLastError();
        LOGW(FATAL) << L"Error creating pipe: " << m_pipeName.c_str()
                    << L" WinAPI error code: 0x" << std::hex << error;
    }

    LOGW(INFO) << L"Succesfully made named pipe: " << m_pipeName.c_str();
}

void Pipe::Write(COMMAND_ENUM cmd, void* ptr, st size = PipeBufferSize)
{
    st vmsgsize = size + sizeof(cmd);
    Message_Internal msgint;
    msgint.cmd = cmd;
    memcpy_s(&msgint.buf, size, ptr, size);


    HANDLE hPipe = INVALID_HANDLE_VALUE;
    DWORD dwWritten = 0;

    hPipe = CreateFile(m_pipeName.c_str(), GENERIC_READ | GENERIC_WRITE, NULL,
                       NULL, OPEN_EXISTING, NULL, NULL);

    if (hPipe == INVALID_HANDLE_VALUE) {
        auto error = GetLastError();
        LOGW(FATAL) << L"Error writing to pipe: " << m_pipeName.c_str()
                    << L" WinAPI error code: 0x" << std::hex << error;
    }

    if (!WriteFile(hPipe, &msgint, vmsgsize, &dwWritten, NULL)) {
        auto error = GetLastError();
        LOGW(WARNING) << L"Error writing to pipe file: " << m_pipeName.c_str()
                    << L" WinAPI error code: 0x" << std::hex << error;
    }
    
    if (dwWritten < vmsgsize) {
        LOGW(WARNING) << L"0 bytes written!";
    }

    CloseHandle(hPipe);
}


st wstringBytes(std::wstring str)
{
    return str.length() * sizeof(wchar_t) + sizeof(L'\0');
}


void Pipe::SendPipedLog(std::wstring msg)
{
    Write(COMMAND_LOG, (void*)(msg.data()), wstringBytes(msg));
}

std::vector<u8> Pipe::writeStringsToBuf(std::vector<std::wstring>& args){
    // First calculate size of buffer
    st size = 0;
    size += sizeof(u32);
    for (auto str : args) {
        size += wstringBytes(str);
    }
    std::vector<u8> buf(size);
    u32* argc = (u32*)buf.data();
    *argc = args.size();
    
    st off = sizeof(u32);
    for (auto str : args) {
        st strsz = wstringBytes(str);
        memcpy_s((void*)((st)(buf.data()) + off), size, str.c_str(), strsz);
        off += strsz;
    }

    return buf;
}

void Pipe::SendPipedCli(std::vector<std::wstring> args) {
    std::vector<u8> clibytes = writeStringsToBuf(args);
    Write(COMMAND_CLI, clibytes.data(), clibytes.size());
}

void Pipe::ParsePipeData(std::vector<u8>& pipeData)
{
    Message_void* vmesg = (Message_void*)(pipeData.data());
    switch (vmesg->cmd) {

        case COMMAND_LOG: {

            Message_log* msglog = (Message_log*)(pipeData.data());
            std::wstring logmsg(&msglog->data);

            for (auto callback : m_c_log) {
                callback(logmsg);
            }

            break;
        }

        case COMMAND_CLI: {

            Message_cli* msgcli = (Message_cli*)(pipeData.data());
            std::vector<std::wstring> argv;

            st off = 0;
            for (auto i = 0; i < msgcli->argc; i++) {
                st strsz = wstringBytes((wchar_t*)((st)(&msgcli->argv) + off));
                std::wstring str((wchar_t*)((st)(&msgcli->argv) + off));
                argv.push_back(str);
                off += strsz;
            }

            for (auto callback : m_c_cli) {
                callback(argv);
            }

            break;
        }

        case COMMAND_TASK: {
        
            Message_data* msdata = (Message_data*)(pipeData.data());
            std::vector<u8> bytes(msdata->data.data, msdata->data.data + msdata->data.size);

            for (auto callback : m_c_data) {
                callback(bytes);
            }

        }

            break;
    }
}

void Pipe::ReadPipeLoop()
{
    std::vector<u8> buf(PipeBufferSize);
    DWORD dwRead = 0; // Num of bytes

        if (ConnectNamedPipe(m_pipeHandle, NULL) != NULL) {
            std::lock_guard<std::mutex> lock(m_loopMtx);
            m_loopInitialized = true;
            m_loopCond.notify_all();
            
            while (ReadFile(m_pipeHandle, buf.data(), PipeBufferSize, &dwRead,
                            NULL) != FALSE) {  
                ParsePipeData(buf);
            }
        }
        // Fallback if failed
        std::lock_guard<std::mutex> lock(m_loopMtx);
        m_loopInitialized = true;
        m_loopCond.notify_all();

    CloseHandle(m_pipeHandle);
}

void Pipe::ConnectPipe()
{
    LOGW(INFO) << L"Connecting to named pipe: " << m_pipeName.c_str();
    std::unique_lock<std::mutex> lock(m_loopMtx);

    m_loopThread = std::thread(&Pipe::ReadPipeLoop, this);
    m_loopThread.detach();

    // There's a chance that ReadPipeLoop is ~1MS too slow, most the this
    // shouldn't be used
    m_loopCond.wait_for(lock, std::chrono::milliseconds(ConnectFallbackMs),
                        [this]() { return m_loopInitialized; });
}

void Pipe::ClosePipe()
{
    // TODO: This wont kill the thread, figure out how to make it kill the
    // thread.
    LOGW(INFO) << L"Closing pipe...";
    m_loopThread.~thread();

    if (m_pipeHandle != INVALID_HANDLE_VALUE) {
        DisconnectNamedPipe(m_pipeHandle);
    }
}

Pipe::~Pipe() { ClosePipe(); }

} // namespace PipeAPI