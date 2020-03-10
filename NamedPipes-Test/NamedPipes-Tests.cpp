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
    pipe1.m_c_log.push_back(func);
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
    g3::internal::shutDownLogging();

    PipeAPI::Pipe pipe1(TestPipeName);
    pipe1.CreatePipe();
    std::function<void(std::vector<std::wstring>)> func = &CliCallback;
    pipe1.m_c_cli.push_back(func);
    pipe1.ConnectPipe();

    PipeAPI::Pipe pipe2(TestPipeName);
    pipe2.SendPipedCli(CliCmds);

    std::unique_lock<std::mutex> lock(log_mutex);
    log_condition.wait(lock, []() { return log_callback; });
    GTEST_SUCCEED();

}

TEST(NamedPipeMessages, Task) { initLogging();

}