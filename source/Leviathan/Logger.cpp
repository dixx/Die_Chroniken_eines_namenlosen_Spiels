#include "Logger.h"

namespace leviathan
{
    namespace core
    {
        Logger::Logger(
                irr::io::IFileSystem* fileSystem,
                irr::ITimer* timer,
                const irr::io::path& fileName,
                const Level globalLogLevel,
                const bool append
        )
        : fileName_(fileName),
          fileSystem_(fileSystem),
          timer_(timer),
          logFile_(0),
          globalLogLevel_(globalLogLevel)
        {
            if ( fileSystem_ == 0 || timer_ == 0 )
                exit( 1 );
            fileSystem_->grab();
            openLogFile( append );
            text = "LogLevel: ";
            addLogLevelName( text, globalLogLevel_ );
            write();
        }

        Logger::~Logger()
        {
            closeLogFile();
            fileSystem_->drop();
        }

        void Logger::write( const Level logLevel )
        {
            if ( logLevel <= globalLogLevel_ )
            {
                irr::core::stringc logline( "" );
                addTimeStamp( logline );
                logline += " [";
                addLogLevelName( logline, logLevel );
                logline += "] ";
                logline += text;
                logline += "\r\n";
                logFile_->write( logline.c_str(), logline.size() );
            }
        }

        void Logger::flush()
        {
            closeLogFile();
            openLogFile();
        }

        /* private: */

        void Logger::openLogFile( const bool append )
        {
            logFile_ = fileSystem_->createAndWriteFile( fileName_, append );
            if ( logFile_ == 0 )
                exit( 1 );
        }

        void Logger::closeLogFile()
        {
            if ( logFile_ != 0 )
            {
                logFile_->drop();
                logFile_ = 0;
            }
        }

        void Logger::addLogLevelName( irr::core::stringc& txt, const Level logLevel )
        {
            switch( logLevel )
            {
                case INFO:
                    txt += "Info";
                    break;
                case DETAIL:
                    txt += "Detail";
                    break;
                case DEBUG:
                    txt += "Debug";
                    break;
                case ALL:
                    txt += "All";
                    break;
                default:
                    txt += "unknown log level!";
            }
        }

        void Logger::addTimeStamp( irr::core::stringc& txt )
        {
            irr::ITimer::RealTimeDate datetime = timer_->getRealTimeAndDate();
            addNumberWithLeadingZero( txt, datetime.Day );
            txt += ".";
            addNumberWithLeadingZero( txt, datetime.Month );
            txt += ".";
            txt += datetime.Year;
            txt += " ";
            addNumberWithLeadingZero( txt, datetime.Hour );
            txt += ":";
            addNumberWithLeadingZero( txt, datetime.Minute );
            txt += ":";
            addNumberWithLeadingZero( txt, datetime.Second );
        }

        void Logger::addNumberWithLeadingZero( irr::core::stringc& txt, const irr::u32 number )
        {
            if( number < 10 )
                txt += '0';
            txt += number;
        }
    }
}
