/*! \file Logger.h
 *  \brief Methoden für das Loggen von Text in eine Datei.
 *  \note Bestandteil der Leviathan Engine
 */

#ifndef LEVIATHAN_CORE_LOGGER_H
#define LEVIATHAN_CORE_LOGGER_H

#include "irrlicht.h"
#include <cstdint>
#include <fstream>

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

            /*! \brief Eine Zeile Text.
             *  \details Da die Irrlicht-Strings bereits sehr mächtige Append-Methoden haben und wir uns den Aufwand
             *           echt sparen können, wird dieser Member ausnahmsweise ohne Getter oder Setter zugänglich
             *           gemacht.
             *  \note Wird geleert sobald er in die Logdatei geschrieben wurde.
             *  \attention Erst initialisieren, dann anhängen!
             */
            irr::core::stringc text;

            /*! \brief Konstruktor.
             *  \param fileName: Logdateiname
             *  \param globalLogLevel: Informationen bis zu diesem Level landen in der Logdatei, alles darüber nicht.
             *  \param append: Wenn `false`, dann wird immer eine neue Logdatei erzeugt. Wenn `true` wird angehängt,
             *         sofern vorhanden.
             */
            Logger(const irr::io::path& fileName, const Level globalLogLevel, const bool append = false);

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
            std::fstream logFile_;  // Stream auf die Logdatei
            Level globalLogLevel_;  // Globales LogLevel

            inline void openLogFile(const irr::io::path& fileName, const bool append = true);
            inline static void addLogLevelName(irr::core::stringc& txt, const Level logLevel);
            inline void addTimeStamp(irr::core::stringc& txt);
        };
    }
}

#endif
