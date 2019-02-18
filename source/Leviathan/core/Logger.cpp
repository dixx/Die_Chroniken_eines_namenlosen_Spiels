#include "Logger.h"
#include <chrono>
#include <ctime>
#include <iomanip>
#include <sstream>


namespace leviathan {
    namespace core {

        Logger::Logger(const irr::io::path& fileName, const Level globalLogLevel, const bool append)
        : text("LogLevel: "),
          fileName_(fileName),
          logFile_(),
          globalLogLevel_(globalLogLevel) {
            openLogFile(append);
            addLogLevelName(text, globalLogLevel_);
            write();
        }

        Logger::~Logger() {
            closeLogFile();
        }

        void Logger::write(const Level logLevel) {
            if (logLevel <= globalLogLevel_) {
                irr::core::stringc logline("");
                addTimeStamp(logline);
                logline += " [";
                addLogLevelName(logline, logLevel);
                logline += "] ";
                logline += text;
                logFile_ << logline.c_str() << std::endl;
            }
        }

        /* private: */

        void Logger::openLogFile(const bool append) {
            auto mode = std::fstream::out;
            if (append)
                mode |= std::fstream::app;
            logFile_.open (fileName_.c_str(), mode);
            if (!logFile_.is_open())
                exit(1);
        }

        void Logger::closeLogFile() {
            if (logFile_.is_open())
                logFile_.close();
        }

        void Logger::addLogLevelName(irr::core::stringc& txt, const Level logLevel) {
            switch (logLevel) {
            case Level::INFO:
                txt += "Info";
                break;
            case Level::DETAIL:
                txt += "Detail";
                break;
            case Level::DEBUG:
                txt += "Debug";
                break;
            case Level::ALL:
                txt += "All";
                break;
            default:
                txt += "unknown log level!";
            }
        }

        void Logger::addTimeStamp(irr::core::stringc& txt) {
            auto now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
            std::stringstream ss;
            ss << std::put_time(std::localtime(&now), "%d.%m.%Y %H:%M:%S");
            txt += ss.str().c_str();
        }
    }
}
