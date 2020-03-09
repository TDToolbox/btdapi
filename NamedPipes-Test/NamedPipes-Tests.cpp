#include "pch.hpp"
#include "CppUnitTest.h"
#include "g3log/g3log.hpp"
#include "g3log/logworker.hpp"
#include "PipeAPI.hpp"
#include "strconv.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

struct LogSink {
    void MsLog(g3::LogMessageMover logEntry)
    {
        auto lm = logEntry.get();
        if (lm.level() != "INFO") {
           Logger::WriteMessage((n2w(lm.level()) + L": " + lm._wmessage + L'\n').c_str());
        }
        else {
            Logger::WriteMessage((lm._wmessage + L'\n').c_str());
        }     
    }
};

namespace NamedPipesTest {
TEST_CLASS(NamedPipesMainTests){

    private :

    public :
        TEST_METHOD(Test){
            using namespace g3;
            std::unique_ptr<LogWorker> logworker{LogWorker::createLogWorker()};
            auto sinkHandle = logworker->addSink(std::make_unique<LogSink>(),
                                                 &LogSink::MsLog);

            initializeLogging(logworker.get());

            LOGW(INFO) << L"Wide Glog hi :)";

            PipeAPI::Pipe pipe(L"NPAPI-TEST-X64-1");
            Assert::AreEqual(0, 0);

            g3::internal::shutDownLogging();
         }
};
}
