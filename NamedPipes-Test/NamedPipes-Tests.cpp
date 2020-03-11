#include "pch.hpp"
#include "strutil.hpp"
#include "PipeAPI.hpp"
#include "g3log/g3log.hpp"
#include "g3log/logworker.hpp"
#include "gtest/gtest.h"
#include <functional>
#include <string>
#include <chrono>
#include <mutex>
#include <condition_variable>


struct LogSink {
    void MsLog(g3::LogMessageMover logEntry)
    {
        auto lm = logEntry.get();
        if (lm.level() != "INFO") {
            std::wstring ostring =
                (n2w(lm.level()) + L": " + lm._wmessage + L'\n');
            std::wcerr << ostring;
            OutputDebugString(ostring.c_str());
        }
        else {
            std::wstring ostring = lm._wmessage + L'\n';
            std::wcerr << ostring;
            OutputDebugString(ostring.c_str());
        }
    }
};

const std::wstring TestPipeName(L"NPAPI-TEST-1");
const std::wstring LogCallbackString(L"Log test callback");
const std::vector<std::wstring> CliCmds = {L"inject", L"btd6.exe", L"-c"};
const st TRY_FOR_MS = 25;

bool loggingInitialized = false;
std::unique_ptr<g3::LogWorker> logworker;

void initLogging() {
    if (!loggingInitialized) {
        logworker = g3::LogWorker::createLogWorker();
        auto sinkHandle =
            logworker->addSink(std::make_unique<LogSink>(), &LogSink::MsLog);

        initializeLogging(logworker.get());
    }

}


bool log_callback = false;
std::mutex log_mutex;
std::condition_variable log_condition;

void LogCallback(std::wstring str){
    if (str == LogCallbackString) {
        std::lock_guard<std::mutex> lock(log_mutex);
        log_callback = true;
        log_condition.notify_one();
    }
    else {
       LOGW(FATAL) << "Failed test!";
    }
}

TEST(NamedPipeMessages, LogMessage)
{
    initLogging();

    PipeAPI::Pipe pipe1(TestPipeName);
    pipe1.CreatePipe();
    std::function<void(std::wstring)> func = &LogCallback;
    pipe1.m_c_log[L"TEST_LOG_CALLBACK"] = func;
    pipe1.ConnectPipe();

    PipeAPI::Pipe pipe2(TestPipeName);
    pipe2.SendPipedLog(LogCallbackString);

    std::unique_lock<std::mutex> lock(log_mutex);
    log_condition.wait(lock, []() { return log_callback; });
    GTEST_SUCCEED();
}

void CliCallback(std::vector<std::wstring> args)
{
    if (args == CliCmds) {
        std::lock_guard<std::mutex> lock(log_mutex);
        log_callback = true;
        log_condition.notify_one();
    }
    else {
        LOGW(FATAL) << "Failed test!";
    }
}

TEST(NamedPipeMessages, CLI) { 

    initLogging();

    PipeAPI::Pipe pipe1(TestPipeName);
    pipe1.CreatePipe();
    std::function<void(std::vector<std::wstring>)> func = &CliCallback;
    pipe1.m_c_cli[L"TEST_CLI_CALLBACK"] = func;
    pipe1.ConnectPipe();

    PipeAPI::Pipe pipe2(TestPipeName);
    pipe2.SendPipedCli(CliCmds);

    std::unique_lock<std::mutex> lock(log_mutex);
    log_condition.wait(lock, []() { return log_callback; });
    GTEST_SUCCEED();

}

static const wchar_t histr[4] = L"Hi!";

struct TestData{
    const wchar_t a[4] = L"Hi!";
    int b = 0x69;
    int c = 0x1337;
};

void DataCallback(std::vector<u8> data)
{
    TestData* dat = (TestData*)(data.data());
    TestData t;
    u32 success = 0;
    if (wcscmp(dat->a, histr) == 0) {
        success++;
    }
    if (dat->b == 0x69) {
        success++;
    }
    if (dat->c == 0x1337) {
        success++;
    }
    if (success == 3) {
        std::lock_guard<std::mutex> lock(log_mutex);
        log_callback = true;
        log_condition.notify_one();
    }
    else {
        LOGW(FATAL) << "Failed test!";
    }
}

TEST(NamedPipeMessages, Data) {

    initLogging();

    PipeAPI::Pipe pipe1(TestPipeName);
    pipe1.CreatePipe();
    std::function<void(std::vector<u8>)> func = &DataCallback;
    pipe1.m_c_data[L"TEST_DATA_CALLBACK"] = func;
    pipe1.ConnectPipe();

    TestData t;

    PipeAPI::Pipe pipe2(TestPipeName);
    pipe2.SendPipedData(&t, sizeof(t));

    std::unique_lock<std::mutex> lock(log_mutex);
    log_condition.wait(lock, []() { return log_callback; });
    GTEST_SUCCEED();

}