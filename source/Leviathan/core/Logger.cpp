#include "Logger.h"
#include <chrono>
#include <ctime>
#include <sstream>

namespace leviathan {
    namespace core {
        Logger::Logger(const char* fileName, const Level globalLogLevel, const bool append)
        : logFile_(),
          globalLogLevel_(globalLogLevel) {
            openLogFile(fileName, append);
            text << "LogLevel: " << logLevelName(globalLogLevel_);
            write();
        }

        Logger::~Logger() {
            if (logFile_.is_open())
                logFile_.close();
        }

        void Logger::write(const Level logLevel) {
            if (logLevel <= globalLogLevel_) {
                std::ostringstream loglinePrefix;
                addTimeStamp(loglinePrefix);
                loglinePrefix << " [" << logLevelName(logLevel) << "] ";
                logFile_ << loglinePrefix.str() << text.str() << std::endl;
            }
            text.str(std::string());
        }

        /* private: */

        void Logger::openLogFile(const char* fileName, const bool append) {
            std::ios_base::openmode mode = std::fstream::out;
            if (append)
                mode |= std::fstream::app;
            logFile_.open(fileName, mode);
            if (!logFile_.is_open())
                exit(1);
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
                return "unknown log level!";
            }
        }

        void Logger::addTimeStamp(std::ostringstream& txt) {
            auto now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
            txt << std::put_time(std::localtime(&now), "%d.%m.%Y %H:%M:%S");
        }
    }
}
