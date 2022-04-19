/*! \file ILogger.h
 *  \brief Lesen und Schreiben der Konfig-Datei sowie Verwaltung der enthaltenen Daten.
 *  \note Bestandteil der Leviathan Engine
 */

#ifndef LEVIATHAN_PUBLIC_INTERFACES_CORE_ILOGGER_H
#define LEVIATHAN_PUBLIC_INTERFACES_CORE_ILOGGER_H

#include <sstream>

namespace leviathan {
    namespace core {

        /*! \interface ILogger
         *  \brief Enthält grundlegende Logging-Funktionen.
         *  \details Das globale LogLevel legt fest, welche Informationen in die Logdatei geschrieben werden.
         *           Je kleiner das LogLevel, desto allgemeiner die Informationen, je größer, desto detaillierter.
         */
        struct ILogger {
            virtual ~ILogger() {}

            /*! \brief Detailtiefe der Meldungen in der Logdatei
             */
            enum class Level {
                INFO = 1,  //!< Informative Sachen für die Logdatei, Warnungen und Fehlermeldungen
                DETAIL = 10,  //!< Details zu Warnungen und Fehlermeldungen
                DEBUG = 100,  //!< Besonders detaillierte Informationen
                ALL = 1000  //!< Alle verfügbaren Informationen
            };

            /*! \brief Zu schreibender Text. Kann beliebig erweitert werden, bevor er mittels `write()`
             *         in die Logdatei geschrieben wird.
             *  \note Wird geleert sobald er in die Logdatei geschrieben wurde.
             */
            std::ostringstream text = std::ostringstream();

            /*! \brief Schreibt eine Zeile Text in die Logdatei
             *  \note Schreibt eine Zeichenkette inklusive "Zeitstempel [LogLevel] " und abschließendem
             *        Zeilenumbruch in die Logdatei, sofern das globalLogLevel größer oder gleich dem angegebenen
             *        LogLevel ist.
             *  \param logLevel: logLevel ab welchem der Text tatsächlich in die Logdatei geschrieben wird
             */
            virtual void write(const Level logLevel = Level::INFO) = 0;
        };
    }
}

#endif
