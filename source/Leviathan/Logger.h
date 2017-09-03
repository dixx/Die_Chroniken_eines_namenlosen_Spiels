/*! \file Logger.h
 *  \brief Methoden für das Loggen von Text in eine Datei.
 *  \note Bestandteil der Leviathan Engine
*/

#ifndef _LEVIATHAN_LOGGER_HEADER
#define _LEVIATHAN_LOGGER_HEADER

#include <irrlicht.h>
#include <cstdint>

namespace leviathan
{
    namespace core
    {

        /*! \class Logger Logger.h "Logger.h"
         *  \brief Enthält grundlegende Logging-Funktionen.
         *  \details Das globale LogLevel legt fest, wie exakt (und welche) Informationen in die Logdatei geschrieben
         *           werden.
         *           Je kleiner das LogLevel, desto allgemeiner die Informationen, je größer, desto detaillierter.
         */
        class Logger
        {

        public:

            /*! \brief Detailtiefe der Meldungen in der Logdatei
             *  \details Es können auch alle Zwischenwerte mit benutzerdefinierten Detailtiefen ergänzt und im Code
             *           verwendet werden, dies hier sind lediglich Richtwerte.
             */
            enum class Level
            {
                INFO   = 1,   //!< Informative Sachen für die Logdatei, Warnungen und Fehlermeldungen
                DETAIL = 10,  //!< Details zu Warnungen und Fehlermeldungen
                DEBUG  = 100, //!< Besonders detaillierte Informationen
                ALL    = 1000 //!< Alle verfügbaren Informationen
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
             *  \param fileSystem: Zeiger auf ein Irrlicht-Dateisystem
             *  \param clock: Zeiger auf das Irrlicht-Zeitsystem
             *  \param fileName: Logdateiname
             *  \param globalLogLevel: Informationen bis zu diesem Level landen in der Logdatei, alles darüber nicht.
             *  \param append: Wenn `false`, dann wird immer eine neue Logdatei erzeugt. Wenn `true` wird angehängt,
             *         sofern vorhanden.
             */
            Logger(
                    irr::io::IFileSystem* fileSystem,
                    irr::ITimer* clock,
                    const irr::io::path& fileName,
                    const Level globalLogLevel,
                    const bool append = false
            );

            /*! \brief Destruktor.
             */
            ~Logger();

            Logger( const Logger& ) = delete;
            Logger& operator=( const Logger& ) = delete;

            /*! \brief Schreibt eine Zeile Text in die Logdatei
             *  \note Schreibt eine Irrlicht-Zeichenkette inklusive "Zeitstempel [LogLevel] " und abschließendem
             *        Zeilenumbruch in die Logdatei, sofern das globalLogLevel größer oder gleich dem angegebenen
             *        LogLevel ist.
             *  \param logLevel: logLevel ab welchem der Text tatsächlich in die Logdatei geschrieben wird
             */
            void write( const Level logLevel = Level::INFO );

            /*! \brief Schreibt den Logdatei-Buffer auf die Platte.
             *  \attention Dies schließt die Logdatei und öffnet sie erneut! (Keine Irrlicht-Implementation dafür
             *             vorhanden)
             *             Nur in Ausnahmefällen benutzen, da die Gefahr besteht, dass sich Prozesse wie z.B. ein
             *             Virenscanner die Logdatei greifen, und Leviathan plötzlich keinen Zugriff mehr auf seine
             *             Logdatei hat! (Das bedeutet: sofortiger Programmabsturz)
             */
            void flush();

        private:

            irr::io::path fileName_; // Logdateiname
            irr::io::IFileSystem* fileSystem_; // Irrlicht-Dateisystem
            irr::ITimer* clock_; // Irrlicht-Zeitsystem
            irr::io::IWriteFile* logFile_; // Logdatei
            Level globalLogLevel_; // Globales LogLevel

            inline void openLogFile( const bool append = true );
            inline void closeLogFile();
            inline void addLogLevelName( irr::core::stringc& txt, const Level logLevel );
            inline void addTimeStamp( irr::core::stringc& txt );
            inline void addNumberWithLeadingZero( irr::core::stringc& txt, const uint32_t number );
        };
    }
}

#endif
