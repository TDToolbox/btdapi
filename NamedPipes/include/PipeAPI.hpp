#pragma once
#include "pch.hpp"
#include "core.hpp"
#include <future>
#include <mutex>
#include <condition_variable>

namespace PipeAPI {

const u32 CurrentVersion = 1;
const u32 HandshakeTimeout = 5000;
const u32 PipeBufferSize = 0xFFFF;

// Hopefully PC's can create a condition variable in <1 MS
// If tests magically start hanging, increase this.
const u32 ConnectFallbackMs = 1;

// u16 has issues with struct alignment
enum COMMAND_ENUM : u32 {
    COMMAND_LOG = 0x0,
    COMMAND_CLI = 0x1,
    COMMAND_TASK = 0x2
};


struct Message_Internal {
    COMMAND_ENUM cmd;
    u8 buf[PipeBufferSize - sizeof(COMMAND_ENUM)];
};

template<typename T>
struct Message {
    COMMAND_ENUM cmd;
    T data;
};

struct DataStruct {
    COMMAND_ENUM cmd;
    u32 size;
    u8* data;
};

//#pragma pack(push, 2)
struct Message_cli {
    COMMAND_ENUM cmd;
    u32 argc;
    wchar_t** argv;
};
//#pragma pack(pop, 2)

typedef Message<void*> Message_void;
// For some reason, &wchar_t* didnt work but &wchar_t did.
typedef Message<wchar_t> Message_log;
//typedef Message<CliStruct> Message_cli;
typedef Message<DataStruct> Message_data;

typedef std::function<void(std::wstring&)> c_log;
typedef std::function<void(std::vector<std::wstring>)> c_cli;
typedef std::function<void(std::vector<u8>)> c_data;

class Pipe {
  private:
    std::wstring m_pipeName;
    vp m_pipeHandle = (vp)(INVALID_HANDLE_VALUE);

    std::thread m_loopThread;
    bool m_loopInitialized = false;
    std::mutex m_loopMtx;
    std::condition_variable m_loopCond;

    void Write(COMMAND_ENUM cmd, void* data, st size);
    void ReadPipeLoop();
    void ParsePipeData(std::vector<u8>& pipeData);
    std::vector<u8> writeStringsToBuf(std::vector<std::wstring>& args);
   // void SendHandshake();
    //void SendHandshakeRecieved();

  public:
    // Callbacks
    std::vector<c_log> m_c_log;
    std::vector<c_cli> m_c_cli;
    std::vector<c_data> m_c_data;

    void SendPipedLog(std::wstring str);
    void SendPipedCli(std::vector<std::wstring> args);
    //void SendPipedData(st size, u8* buf);

    void CreatePipe();
    void ConnectPipe();
    void ClosePipe();

    Pipe(std::wstring PipeName);
    ~Pipe();
};

}