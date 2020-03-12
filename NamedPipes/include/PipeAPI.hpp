#pragma once
#include "pch.hpp"
//
#include "core.hpp"
#include <condition_variable>
#include <future>
#include <mutex>
#include <unordered_map>

namespace PipeAPI {

const u32 CurrentVersion = 1;
const u32 HandshakeTimeout = 5000;
const u32 PipeBufferSize = 0xFFFF;

// u16 has issues with struct alignment
enum COMMAND_ENUM : u32 {
    COMMAND_LOG = 0x0,
    COMMAND_CLI = 0x1,
    COMMAND_DATA = 0x2
};

struct Message_Internal {
    COMMAND_ENUM cmd;
    u8 buf[PipeBufferSize - sizeof(COMMAND_ENUM)];
};

struct Message_void {
    COMMAND_ENUM cmd;
    void* data;
};

struct Message_log {
    COMMAND_ENUM cmd;
    wchar_t msg;
    // For some reason, &wchar_t* didnt work but &wchar_t did.
};

struct DataStruct {
    COMMAND_ENUM cmd;
    u32 size;
    u8* data;
};

struct Message_cli {
    COMMAND_ENUM cmd;
    u32 argc;
    wchar_t** argv;
};

typedef std::function<void(std::wstring&)> c_log;
typedef std::function<void(std::vector<std::wstring>)> c_cli;
typedef std::function<void(std::vector<u8>)> c_data;

class Pipe {
  private:
    std::wstring m_pipeName;
    vp m_pipeHandle = (vp)(INVALID_HANDLE_VALUE);

    std::thread m_loopThread;

    void Write(COMMAND_ENUM cmd, void* data, st size);
    void ReadPipeLoop(std::promise<void>&& loopPromises);
    void ParsePipeData(std::vector<u8>& pipeData);
    std::vector<u8> writeStringsToBuf(std::vector<std::wstring>& args);

  public:
    // Callbacks
    std::unordered_map<std::wstring, c_log> m_c_log;
    std::unordered_map<std::wstring, c_cli> m_c_cli;
    std::unordered_map<std::wstring, c_data> m_c_data;

    void SendPipedLog(std::wstring str);
    void SendPipedCli(std::vector<std::wstring> args);
    void SendPipedData(void* buf, u32 size);

    void CreatePipe();
    void ConnectPipe();
    void ClosePipe();

    Pipe(std::wstring PipeName);
    ~Pipe();
};

} // namespace PipeAPI