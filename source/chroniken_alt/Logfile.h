/*! \file Logfile.h
 *  \brief Klasse (Singleton) mit verschiedenen Methoden für das Loggen von Daten in eine Datei.
 */

#ifndef _LOGFILE_HEADER
#define _LOGFILE_HEADER

#include <irrlicht.h>

/*! \class Logfile Logfile.h "Logfile.h"
 *  \brief Enthält grundlegende Logging-Funktionen.
 *  \details Das globale LogLevel legt fest, wie exakt (und welche) Informationen ins Logfile geschrieben werden.
 *           Je kleiner das LogLevel, desto allgemeiner die Informationen, je größer, desto detaillierter.
 *  \attention Klasse ist `Singleton`.\n Ein Zeiger auf eine Instanz des Irrlicht-Dateisystems wird benötigt.
 *  \note Instanzierung: `Logfile& myLogfile = Logfile::getInstance( filesystem, "filename.log", INFO );`
 *        \n Oder: `Logfile::getInstance( fs, "filename.log", INFO );`
 *        \n Benutzen: `myLogfile.writeLine( DETAIL, "Bad thing happened: ", thing );`
 *        \n Oder: `Logfile::getInstance().writeLine( INFO, "Setup done." );`
 */
class Logfile
{

public:

    /*! \brief Detailtiefe der Meldungen im Logfile
     *
     *  Es können auch alle Zwischenwerte mit benutzerdefinierten Detailtiefen ergänzt und im Code verwendet werden,
     *  dies hier sind lediglich Richtwerte.
     */
    enum LogLevel
    {
        INFO   = 1,             //!< Informative Sachen für das Logfile,
                                //!  Warnungen und Fehlermeldungen
        DETAIL = 10,            //!< Details zu Warnungen und Fehlermeldungen
        DEBUG  = 100,           //!< Besonders detaillierte Informationen
        ALL    = 1000           //!< Alle verfügbaren Informationen
    };

    /*! \brief Ersatz für den Konstruktor.
     *
     *  Instanziert die Klasse einmalig und verhindert Mehrfachinstanzierung. Logdatei wird geöffnet und globales
     *  LogLevel wird festgelegt. Das globale LogLevel legt hierbei fest,
     *  bis zu welcher Detailtiefe Informationen in das Log geschrieben werden (siehe enum LogLevel).
     *  \param fs (\a io::IFileSystem*) Zeiger auf das Irrlicht-Dateisystem
     *  \param filename (\a const \a path&) Name und Pfad der Logdatei
     *  \param logginglevel (\a const \a u16) globales Logging-Level
     *  \return Referenz auf die einzige Instanz dieser Klasse
     */
    static Logfile& getInstance(
            irr::io::IFileSystem* fs = 0,
            const irr::io::path& filename = "DuHastDenLogdateinamenVergessen.txt",
            const irr::u16 logginglevel = INFO
    );

    /*! \brief Schreibt Text in das Logfile
     *  \note Schreibt eine Irrlicht-Zeichenkette in das Logfile, wenn das Logginglevel kleiner oder gleich dem
     *        globalLogLevel ist.
     *  \param logginglevel (\a const \a u16) Logginglevel
     *  \param logline (\a const \a core::stringc&) Text
     *  \return -
     */
    void write( const irr::u16 logginglevel, const irr::core::stringc& logline );

    /*! \brief Schreibt Text und Daten in das Logfile
     *  \note Schreibt eine Irrlicht-Zeichenkette und eine Zahl beliebigen Typs in das Logfile, wenn das Logginglevel
     *        kleiner oder gleich dem globalLogLevel ist.
     *  \param logginglevel (\a const \a u16) Logginglevel
     *  \param logline (\a const \a core::stringc&) Text
     *  \param number (\a const \a beliebiger \a Zahlentyp) Zahl
     *  \return -
     */
    // Da diese Funktion für verschiedene Zahlentypen gilt, und das durch ein Template realisiert wird,
    // muss der Body leider in der Headerdatei angelegt werden.
    template <typename T>
    void write( const irr::u16 logginglevel, const irr::core::stringc& logline, const T number )
    {
        if ( logginglevel <= globalLogLevel_ )
        {
            openLogfile();
            if ( logginglevel == DEBUG )
                logfile_->write( debugPrefix_.c_str(), debugPrefixSize_ );
            logfile_->write( logline.c_str(), logline.size() );
            logfile_->write( irr::core::stringc( number ).c_str(), irr::core::stringc( number ).size() );
            closeLogfile();
        }
    }

    /*! \brief Schreibt Text mit abschließendem Zeilenumbruch in das Logfile
     *  \note Schreibt eine Irrlicht-Zeichenkette mit abschließendem Zeilenumbruch in das Logfile, wenn das
     *        Logginglevel kleiner oder gleich dem globalLogLevel ist.
     *  \param logginglevel (\a const \a u16) Logginglevel
     *  \param logline (\a const \a core::stringc&) Text
     *  \return -
     */
    void writeLine( const irr::u16 logginglevel, const irr::core::stringc& logline );

    /*! \brief Schreibt Text und Daten mit abschließendem Zeilenumbruch in das Logfile
     *  \note Schreibt eine Irrlicht-Zeichenkette und eine Zahl beliebigen Typs mit abschließendem Zeilenumbruch in das
     *        Logfile, wenn das Logginglevel kleiner oder gleich dem globalLogLevel ist.
     *  \param logginglevel (\a const \a u16) Logginglevel
     *  \param logline (\a const \a core::stringc&) Text
     *  \param number (\a const \a beliebiger \a Zahlentyp) Zahl
     *  \return -
     */
    // Da diese Funktion für verschiedene Zahlentypen gilt, und das durch ein Template realisiert wird,
    // muss der Body leider in der Headerdatei angelegt werden.
    template <typename T>
    void writeLine( const irr::u16 logginglevel, const irr::core::stringc& logline, const T number )
    {
        if ( logginglevel <= globalLogLevel_ )
        {
            openLogfile();
            if ( logginglevel == DEBUG )
                logfile_->write( debugPrefix_.c_str(), debugPrefixSize_ );
            logfile_->write( logline.c_str(), logline.size() );
            logfile_->write( irr::core::stringc( number ).c_str(), irr::core::stringc( number ).size() );
            logfile_->write( newLine_.c_str(), newLineSize_ );
            closeLogfile();
        }
    }

    /*! \brief Ändert den Zeiger auf ein Irrlicht-Filesystem.
     *  \attention Dies ist notwendig, wenn das Entchen zerstört und neu erstellt wurde!
     *  \param fs (\a io::IFileSystem*) Zeiger auf das virtuelle Dateisystem
     *  \return -
     */
    void setNewFilesystem( irr::io::IFileSystem* fs = 0 );

    /*! \brief Schließt das Logfile und bricht die Programabarbeitung hart ab.
     *  \attention Belegter Speicher wird nicht freigegeben!
     *  \param logline (\a const \a core::stringc&) Text
     *  \return -
     */
    void emergencyExit( const irr::core::stringc& logline );

    /*! \brief Schreibt Text mit abschließendem Zeilenumbruch in das Logfile
     *  \note Schreibt im DEBUG-Modus eine Irrlicht-Zeichenkette mit abschließendem Zeilenumbruch in das Logfile.
     *  \param logline (\a const \a core::stringc&) Text
     *  \param number (\a const \a beliebiger \a Zahlentyp) Zahl
     *  \return -
     */
    // Da diese Funktion für verschiedene Zahlentypen gilt, und das durch ein Template realisiert wird,
    // muss der Body leider in der Headerdatei angelegt werden.
    template <typename T>
    void dbg( const irr::core::stringc& logline, const T number )
    {
        writeLine( DEBUG, logline, number );
    }
    void dbg( const irr::core::stringc& logline, const irr::core::vector3df& vector )
    {
        write( DEBUG, logline );
        write( DEBUG - 1, "(", vector.X );
        write( DEBUG - 1, ", ", vector.Y );
        write( DEBUG - 1, ", ", vector.Z );
        writeLine( DEBUG - 1, ")" );
    }

private:

    irr::io::path filename_;  // Logdateiname
    irr::io::IFileSystem* fs_;  // Irrlicht-Dateisystem
    irr::io::IWriteFile* logfile_;  // Logdatei
    irr::u32 globalLogLevel_;  // Globales LogLevel
    irr::core::stringc newLine_;  // Maske fuer einen Zeilenumbruch
    irr::u32 newLineSize_;  // Bytegroesse von Zeilenumbruch
    irr::core::stringc debugPrefix_;  // Maske fuer Prefix [debug]
    irr::u32 debugPrefixSize_;  // Bytegroesse von Prefix [debug]

    Logfile( irr::io::IFileSystem* fs, const irr::io::path& filename,
            const irr::u16 logginglevel );  // ctor. Von aussen keine Instanzen direkt erzeugbar
    Logfile( const Logfile& );  // Instanz ist nicht kopierbar
    Logfile& operator=( const Logfile& );  // Instanz ist nicht zuweisbar
    ~Logfile();  // dtor. Instanz zerstoert sich bei Programmende

    inline void openLogfile()
    {
        logfile_ = fs_->createAndWriteFile( filename_, /* append = */ true );
        if ( logfile_ == 0 )
            exit( 1 );
    }

    inline void closeLogfile()
    {
        if ( logfile_ != 0 )
        {
            logfile_->drop();
            logfile_ = 0;
        }
    }

};

#endif
