#include "Logger.h"
#include <chrono>
#include <ctime>

namespace leviathan {
    namespace core {
        Logger::Logger(const char* fileName, const Level globalLogLevel, const bool append)
        : mLogFile(), mGlobalLogLevel(globalLogLevel) {
            openLogFile(fileName, append);
            text << "LogLevel: " << logLevelName(mGlobalLogLevel);
            write();
        }

        Logger::~Logger() {
            if (mLogFile.is_open()) mLogFile.close();
        }

        void Logger::write(const Level logLevel) {
            if (logLevel <= mGlobalLogLevel) {
                std::ostringstream loglinePrefix;
                addTimeStamp(loglinePrefix);
                loglinePrefix << " [" << logLevelName(logLevel) << "] ";
                mLogFile << loglinePrefix.str() << text.str() << std::endl;
            }
            text.str(std::string());
        }

        /* private: */

        void Logger::openLogFile(const char* fileName, const bool append) {
            std::ios_base::openmode mode = std::fstream::out;
            if (append) mode |= std::fstream::app;
            mLogFile.open(fileName, mode);
            if (!mLogFile.is_open()) exit(1);
        }

        std::string Logger::logLevelName(const Level logLevel) {
            switch (logLevel) {
            case Level::INFO:
                return "Info";
            case Level::DETAIL:
                return "Detail";
            case Level::DEBUG:
                return "Debug";
            case Level::ALL:
                return "All";
            default:
                return "custom log level";
            }
        }

        void Logger::addTimeStamp(std::ostringstream& txt) {
            auto now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
            txt << std::put_time(std::localtime(&now), "%d.%m.%Y %H:%M:%S");
        }
    }
}
