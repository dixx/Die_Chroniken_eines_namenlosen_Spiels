/*! \file Logger.h
 *  \brief Methoden für das Loggen von Text in eine Datei.
 *  \note Bestandteil der Leviathan Engine
 */

#ifndef LEVIATHAN_CORE_LOGGER_H
#define LEVIATHAN_CORE_LOGGER_H

// #include <filesystem> // TODO: use this as soon as it is available in mingw!
#include <fstream>
#include <iomanip>
#include <sstream>

namespace leviathan {
    namespace core {

        /*! \class Logger Logger.h "Logger.h"
         *  \brief Enthält grundlegende Logging-Funktionen.
         *  \details Das globale LogLevel legt fest, wie exakt (und welche) Informationen in die Logdatei geschrieben
         *           werden.
         *           Je kleiner das LogLevel, desto allgemeiner die Informationen, je größer, desto detaillierter.
         */
        class Logger {
        public:
            /*! \brief Detailtiefe der Meldungen in der Logdatei
             *  \details Es können auch alle Zwischenwerte mit benutzerdefinierten Detailtiefen ergänzt und im Code
             *           verwendet werden, dies hier sind lediglich Richtwerte.
             */
            enum class Level {
                INFO = 1,  //!< Informative Sachen für die Logdatei, Warnungen und Fehlermeldungen
                DETAIL = 10,  //!< Details zu Warnungen und Fehlermeldungen
                DEBUG = 100,  //!< Besonders detaillierte Informationen
                ALL = 1000  //!< Alle verfügbaren Informationen
            };

            /*! \brief Zu schreibender Text.
             *  \note Wird geleert sobald er in die Logdatei geschrieben wurde.
             */
            std::ostringstream text = std::ostringstream();

            /*! \brief Konstruktor.
             *  \param fileName: Logdateiname
             *  \param globalLogLevel: Informationen bis zu diesem Level landen in der Logdatei, alles darüber nicht.
             *  \param append: Wenn `false`, dann wird immer eine neue Logdatei erzeugt. Wenn `true` wird angehängt,
             *         sofern vorhanden.
             */
            Logger(const char* fileName, const Level globalLogLevel, const bool append = false);

            /*! \brief Destruktor.
             */
            ~Logger();

            Logger() = delete;
            Logger(const Logger&) = delete;
            Logger& operator=(const Logger&) = delete;

            /*! \brief Schreibt eine Zeile Text in die Logdatei
             *  \note Schreibt eine Irrlicht-Zeichenkette inklusive "Zeitstempel [LogLevel] " und abschließendem
             *        Zeilenumbruch in die Logdatei, sofern das globalLogLevel größer oder gleich dem angegebenen
             *        LogLevel ist.
             *  \param logLevel: logLevel ab welchem der Text tatsächlich in die Logdatei geschrieben wird
             */
            void write(const Level logLevel = Level::INFO);

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
