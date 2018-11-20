#include "Logger.h"

namespace leviathan {
    namespace core {

        Logger::Logger(
            irr::io::IFileSystem* fileSystem,
            irr::ITimer* clock,
            const irr::io::path& fileName,
            const Level globalLogLevel,
            const bool append)
        : text("LogLevel: "),
          fileName_(fileName),
          fileSystem_(fileSystem),
          clock_(clock),
          globalLogLevel_(globalLogLevel) {
            if (!fileSystem_ || !clock_)
                exit(1);
            fileSystem_->grab();
            openLogFile(append);
            addLogLevelName(text, globalLogLevel_);
            write();
        }

        Logger::~Logger() {
            closeLogFile();
            fileSystem_->drop();
        }

        void Logger::write(const Level logLevel) {
            if (logLevel <= globalLogLevel_) {
                irr::core::stringc logline("");
                addTimeStamp(logline);
                logline += " [";
                addLogLevelName(logline, logLevel);
                logline += "] ";
                logline += text;
                logline += "\r\n";
                logFile_->write(logline.c_str(), logline.size());
            }
        }

        void Logger::flush() {
            closeLogFile();
            openLogFile();
        }

        /* private: */

        void Logger::openLogFile(const bool append) {
            logFile_ = fileSystem_->createAndWriteFile(fileName_, append);
            if (!logFile_)
                exit(1);
        }

        void Logger::closeLogFile() {
            if (logFile_) {
                logFile_->drop();
                logFile_ = nullptr;
            }
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
            auto now = clock_->getRealTimeAndDate();
            addNumberWithLeadingZero(txt, now.Day);
            txt += ".";
            addNumberWithLeadingZero(txt, now.Month);
            txt += ".";
            txt += now.Year;
            txt += " ";
            addNumberWithLeadingZero(txt, now.Hour);
            txt += ":";
            addNumberWithLeadingZero(txt, now.Minute);
            txt += ":";
            addNumberWithLeadingZero(txt, now.Second);
        }

        void Logger::addNumberWithLeadingZero(irr::core::stringc& txt, const uint32_t number) {
            if (number < 10)
                txt += '0';
            txt += number;
        }
    }
}
