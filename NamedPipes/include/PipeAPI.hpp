#pragma once
#include "pch.hpp"
#include "core.hpp"

namespace PipeAPI {

const u32 CurrentVersion = 1;
const u32 HandshakeTimeout = 5000;
const u32 PipeBufferSize = 0xFFFF;

enum COMMAND_ENUM : u16 {
    COMMAND_HANDSHAKE_SEND = 0x0,
    COMMAND_HANDSHAKE_RECIEVED = 0x1,
    COMMAND_LOG = 0x2,
    COMMAND_CLI = 0x3,
    COMMAND_TASK = 0x4
};

struct Message {
    u64 size;
    COMMAND_ENUM cmd;
};

typedef std::function<void(std::wstring&)> c_log;
typedef std::function<void(std::vector<std::wstring>&)> c_cli;
typedef std::function<void(u8*)> c_data;

class Pipe {
  private:
    std::wstring m_pipeName;
    vp m_pipeHandle = (vp)(INVALID_HANDLE_VALUE);

    void CreatePipe();
    void ConnectPipe();
    void ClosePipe();

  public:
    // Callbacks
    std::vector<c_log> m_c_log;
    std::vector<c_cli> m_c_cli;
    std::vector<c_log> m_c_data;

    Pipe(std::wstring PipeName);
    ~Pipe();
};

}