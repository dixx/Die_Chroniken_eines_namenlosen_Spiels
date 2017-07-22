#include "SaveGames.h"
#include "GenericHelperMethods.h"
#include "Logfile.h"

// these defines are for better readability only
#define UNKNOWN_SAVEGAME_FORMAT "Unbekanntes Savegame-Format! Abbruch."
#define BROKEN_STREAM "Schreiben in Savegame-Datei fehlgeschlagen! Abbruch."



SaveGames::SaveGames( irr::IrrlichtDevice* device )
: device_(device),
  fs_(0),
  savegameName_(""),
  applicationDirectory_(),
  savegamesDirectory_(),
  CURRENT_VERSION(2)
{
    if ( device_ == 0 )
        Logfile::getInstance().emergencyExit( "Entchen in [SaveGames] nicht mehr gefunden! Abbruch.");
    fs_ = device_->getFileSystem();
    applicationDirectory_ = fs_->getWorkingDirectory();
    savegamesDirectory_ = applicationDirectory_ + "/SAVEGAMES";
    irr::io::IFileList* dirTree = fs_->createFileList();
    if ( dirTree->findFile( savegamesDirectory_, true ) == -1 )
        Logfile::getInstance().emergencyExit( savegamesDirectory_ + " nicht gefunden! Abbruch." );
    dirTree->drop();
}



SaveGames::~SaveGames()
{
    // Niemals droppen, wenn Objekt nicht durch "create" erzeugt wurde!
}



void SaveGames::load( const irr::io::path& filename )
{
    /**/Logfile& log = Logfile::getInstance();
    GenericHelperMethods::getInstance().validateFileExistence( filename );
    irr::io::IReadFile* stream = fs_->createAndOpenFile( filename );
    checkVersion( read<irr::u8>( stream ) );
    skip<irr::u32>( stream ); // so far, timestamp is here of no interest
    /**/log.writeLine( Logfile::DEBUG, "hero: ", readString( stream ) );
    /**/log.writeLine( Logfile::DEBUG, "level: ", readString( stream ) );
    stream->drop();
}



const irr::io::path& SaveGames::findNewest()
{
    fs_->changeWorkingDirectoryTo( savegamesDirectory_ );
    irr::io::IFileList* fileList = fs_->createFileList();
    fs_->changeWorkingDirectoryTo( applicationDirectory_ );
    savegameName_ = "";
    irr::io::IReadFile* stream = 0;
    irr::u32 newestTimestamp = 0;
    for ( register irr::u32 i = 0; i < fileList->getFileCount(); ++i )
    {
        if ( fileList->getFileName( i ).find( ".sav" ) == -1 )
            continue;
        const irr::io::path& filename = fileList->getFullFileName( i );
        stream = fs_->createAndOpenFile( filename );
        if ( !stream )
        {
            Logfile::getInstance().writeLine( Logfile::INFO, "Lesen von Datei fehlgeschlagen: ", filename );
            continue;
        }
        checkVersion( read<irr::u8>( stream ) );
        irr::u32 timestamp = read<irr::u32>( stream );
        if ( timestamp > newestTimestamp )
        {
            savegameName_ = filename;
            newestTimestamp = timestamp;
        }
        stream->drop();
        stream = 0;
    }
    fileList->drop();
    return savegameName_;
}

// TODO on successful character creation, create one savegame, clone the other two from it.


void SaveGames::save( const irr::io::path& filename )
{
    irr::io::IWriteFile* stream = fs_->createAndWriteFile( filename );
    if ( !stream )
    {
        Logfile::getInstance().writeLine( Logfile::INFO, "Savegame: ", filename);
        Logfile::getInstance().emergencyExit( BROKEN_STREAM );
    }
    write<irr::u8>( stream, CURRENT_VERSION );
    write<irr::u32>( stream, getTimestamp() );
    irr::core::stringc heroData = "ONAMEder edle Testheld@OTYPEPUNK@MOFFS0.0x0.6x0.0@MROTA0.0x-90.0x0.0";
    heroData += "@MSCAL0.025x0.025x0.025@POSXZ11.0x11.0@MTEX0GFX/sydney.bmp@MFILEGFX/OBJECTS/sydney.md2";
    writeString( stream, heroData );
    writeString( stream, "Level_X" );
    stream->drop();
}



/* private */


// TODO File-Methoden auslagern nach eigener Klasse!
template <typename T> T SaveGames::read( irr::io::IReadFile* stream )
{
    T buffer;
    irr::u32 bytes = sizeof( T );//typeof( buffer ) );
    if ( stream->read( &buffer, bytes ) < static_cast<irr::s32>( bytes ) )
        Logfile::getInstance().emergencyExit( UNKNOWN_SAVEGAME_FORMAT );
    return buffer;
}



irr::core::stringc SaveGames::readString( irr::io::IReadFile* stream )
{
    irr::u32 count = read<irr::u32>( stream );
    irr::u8* buffer = new irr::u8[count];
    if ( stream->read( buffer, count ) < static_cast<irr::s32>( count ) )
        Logfile::getInstance().emergencyExit( UNKNOWN_SAVEGAME_FORMAT );
    irr::core::stringc ret = irr::core::stringc( buffer );
    delete[] buffer;
    return ret;
}



template <typename T> void SaveGames::write( irr::io::IWriteFile* stream, const T& number )
{
    if ( stream->write( &number, sizeof( T ) ) < static_cast<irr::s32>( sizeof( T ) ) )
        Logfile::getInstance().emergencyExit( BROKEN_STREAM );
}
// explicit instantiations:
template void SaveGames::write<irr::u8>( irr::io::IWriteFile* stream, const irr::u8& number );
template void SaveGames::write<irr::u32>( irr::io::IWriteFile* stream, const irr::u32& number );



void SaveGames::writeString( irr::io::IWriteFile* stream, const irr::core::stringc& text )
{
    irr::u32 count = text.size() + 1; // + 1 == trailing \0
    if ( stream->write( &count, sizeof( irr::u32 ) ) < static_cast<irr::s32>( sizeof( irr::u32 ) ) )
        Logfile::getInstance().emergencyExit( BROKEN_STREAM );
    if ( stream->write( text.c_str(), count ) < static_cast<irr::s32>( count ) )
        Logfile::getInstance().emergencyExit( BROKEN_STREAM );
}



template <typename T> void SaveGames::skip( irr::io::IReadFile* stream )
{
    if ( !stream->seek( sizeof( T ), true ) )
        Logfile::getInstance().emergencyExit( UNKNOWN_SAVEGAME_FORMAT );
}
// explicit instantiations:
template void SaveGames::skip<irr::u32>( irr::io::IReadFile* stream );



void SaveGames::checkVersion( irr::u8 version )
{
    // TODO create backward-compatibility later
    if ( version != CURRENT_VERSION )
    {
        irr::core::stringc errorMessage = "Savegame-Version ";
        errorMessage += version;
        errorMessage += " unbekannt! Abbruch.";
        Logfile::getInstance().emergencyExit( errorMessage );
    }
}



irr::u32 SaveGames::getTimestamp()
{
    /* get seconds elapsed since 1970-01-01 */
    irr::ITimer::RealTimeDate datetime = device_->getTimer()->getRealTimeAndDate();
    if ( datetime.Year < 1970 )
        datetime.Year = 1970; // to avoid compatibility errors on systems with wrong date settings
    if ( datetime.IsDST )
        datetime.Hour--; // adjust hours of day with daylight saving time
    irr::u32 m = ( datetime.Month + 9 ) % 12;
    irr::u32 y = static_cast<irr::u32>( datetime.Year ) - m / 10;
    irr::u32 days_since_1970 =
            y * 365 + y / 4 - y / 100 + y / 400
            + ( m * 306 + 5 ) / 10
            + datetime.Day - 1 // <-- days from 0000-01-01 until today
            - 719468; // days from 0000-01-01 until 1970-01-01
    return datetime.Second
        + datetime.Minute * 60
        + datetime.Hour * 3600 // BUG: #21, we have offset from GTM here!
        + days_since_1970 * 86400;
}
