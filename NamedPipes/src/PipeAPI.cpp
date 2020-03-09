#include "pch.hpp"
#include "PipeAPI.hpp"
#include "Config.hpp"
#include "g3log/g3log.hpp"


namespace PipeAPI {

Pipe::Pipe(std::wstring PipeName)
{
    m_pipeName = L"\\\\.\\pipe\\" + PipeName;

    LOGW(INFO) << L"Creating named pipe: " << m_pipeName.c_str();

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

void Pipe::ClosePipe()
{
    if (m_pipeHandle != INVALID_HANDLE_VALUE) {
        DisconnectNamedPipe(m_pipeHandle);
    }
}

Pipe::~Pipe() { ClosePipe(); }

} // namespace PipeAPI