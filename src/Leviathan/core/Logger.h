/*! \file Logger.h
 *  \brief Methoden für das Loggen von Text in eine Datei.
 *  \note Bestandteil der Leviathan Engine
 */

#ifndef LEVIATHAN_CORE_LOGGER_H
#define LEVIATHAN_CORE_LOGGER_H

// #include <filesystem> // TODO: use this as soon as it is available in mingw!
#include <core/ILogger.h>
#include <fstream>
#include <iomanip>
#include <string>

namespace leviathan {
    namespace core {

        /*! \class Logger Logger.h "Logger.h"
         *  \brief Enthält grundlegende Logging-Funktionen.
         *  \details Das globale LogLevel legt fest, welche Informationen in die Logdatei geschrieben werden.
         *           Je kleiner das LogLevel, desto allgemeiner die Informationen, je größer, desto detaillierter.
         */
        class Logger final : public ILogger {
        public:
            /*! \brief Konstruktor.
             *  \param fileName: Logdateiname
             *  \param globalLogLevel: Informationen bis zu diesem Level landen in der Logdatei, alles darüber nicht.
             *  \param append: Wenn `false`, dann wird eine neue Logdatei erzeugt. Wenn `true` wird angehängt,
             *         sofern vorhanden.
             */
            Logger(const char* fileName, const Level globalLogLevel, const bool append = false);

            /*! \brief Destruktor.
             */
            ~Logger();

            Logger() = delete;
            Logger(const Logger&) = delete;
            Logger& operator=(const Logger&) = delete;

            void write(const Level logLevel = Level::INFO) override;

        private:
            std::fstream logFile_;
            Level globalLogLevel_;

            inline void openLogFile(const char* fileName, const bool append = true);
            inline static std::string logLevelName(const Level logLevel);
            inline static void addTimeStamp(std::ostringstream& txt);
        };
    }
}

#endif
