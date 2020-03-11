#include "pch.hpp"
#include "PipeAPI.hpp"
#include "Config.hpp"
#include "g3log/g3log.hpp"
#include <thread>
#include "strutil.hpp"

namespace PipeAPI {

Pipe::Pipe(std::wstring PipeName) { m_pipeName = L"\\\\.\\pipe\\" + PipeName; }

//
// Pipe Init
//

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

void Pipe::ConnectPipe()
{
    LOGW(INFO) << L"Connecting to named pipe: " << m_pipeName.c_str();

    // Huge thanks to Argh#2682 for helping with threading
    std::promise<void> loopPromise;
    std::future<void> fut = loopPromise.get_future();

    m_loopThread =
        std::thread(&Pipe::ReadPipeLoop, this, std::move(loopPromise));
    m_loopThread.detach();

    fut.get();
}

//
// Pipe sending
//

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

std::vector<u8> Pipe::writeStringsToBuf(std::vector<std::wstring>& args)
{
    // Get size
    st size = 0;
    size += sizeof(u32);
    for (auto str : args) {
        size += wstringBytes(str);
    }
    std::vector<u8> buf(size);

    // Set size
    u32* argc = (u32*)buf.data();
    *argc = args.size();

    // Write strings
    st off = sizeof(u32);
    for (auto str : args) {
        st strsz = wstringBytes(str);
        memcpy_s((void*)((st)(buf.data()) + off), size, str.c_str(), strsz);
        off += strsz;
    }

    return buf;
}

void Pipe::SendPipedCli(std::vector<std::wstring> args)
{
    std::vector<u8> clibytes = writeStringsToBuf(args);
    Write(COMMAND_CLI, clibytes.data(), clibytes.size());
}

void Pipe::SendPipedLog(std::wstring msg)
{
    Write(COMMAND_LOG, (void*)(msg.data()), wstringBytes(msg));
}

void Pipe::SendPipedData(void* buf, u32 size)
{
    DataStruct* ds = (DataStruct*)(malloc(size + sizeof(size)));
    ds->size = size;
    memcpy_s(&ds->data, size, buf, size);

    Write(COMMAND_DATA, &ds->size, size + sizeof(size));

    // TODO: Investigate potential memory leak
    //free(ds);
}

//
// Pipe reading
//

void Pipe::ParsePipeData(std::vector<u8>& pipeData)
{
    Message_void* vmesg = (Message_void*)(pipeData.data());
    switch (vmesg->cmd) {

        case COMMAND_LOG: {

            Message_log* msglog = (Message_log*)(pipeData.data());
            std::wstring logmsg(&msglog->msg);

            for (auto const& callback : m_c_log) {
                callback.second(logmsg);
            }

            break;
        }

        case COMMAND_CLI: {

            Message_cli* msgcli = (Message_cli*)(pipeData.data());
            std::vector<std::wstring> argv;

            st off = 0;
            for (u32 i = 0; i < msgcli->argc; i++) {
                st strsz = wstringBytes((wchar_t*)((st)(&msgcli->argv) + off));
                std::wstring str((wchar_t*)((st)(&msgcli->argv) + off));
                argv.push_back(str);
                off += strsz;
            }

            for (auto const& callback : m_c_cli) {
                callback.second(argv);
            }

            break;
        }

        case COMMAND_DATA: {

            DataStruct* msdata = (DataStruct*)(pipeData.data());
            std::vector<u8> bytes(
                (u8*)(&msdata->data),
                (u8*)((st)(&msdata->data) + (st)(msdata->size)));

            for (auto const& callback : m_c_data) {
                callback.second(bytes);
            }

        }

            break;
    }
}

void Pipe::ReadPipeLoop(std::promise<void>&& loopPromise)
{
    std::vector<u8> buf(PipeBufferSize);
    DWORD dwRead = 0; // Num of bytes

        loopPromise.set_value();

        if (ConnectNamedPipe(m_pipeHandle, NULL) != NULL) {
                   
            while (ReadFile(m_pipeHandle, buf.data(), PipeBufferSize, &dwRead,
                            NULL) != FALSE) {  
                ParsePipeData(buf);
            }
        }
        else {
            auto error = GetLastError();
            LOGW(FATAL) << L"Error connecting pipe: " << m_pipeName.c_str()
                        << L" WinAPI error code: 0x" << std::hex << error;
        }

    CloseHandle(m_pipeHandle);
}

//
// Pipe de-init
//

void Pipe::ClosePipe()
{
    // TODO: This wont kill the thread since its detached, 
    // figure out how to make it kill the thread.
    LOGW(INFO) << L"Closing pipe...";
    m_loopThread.~thread();

    if (m_pipeHandle != INVALID_HANDLE_VALUE) {
        DisconnectNamedPipe(m_pipeHandle);
    }
}

Pipe::~Pipe() { ClosePipe(); }

} // namespace PipeAPI