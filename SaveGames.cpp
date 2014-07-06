#include "SaveGames.h"
#include "GenericHelperMethods.h"
#include "Logfile.h"

// these defines are for better readability only
#define UNKNOWN_SAVEGAME_FORMAT "Unbekanntes Savegame-Format! Abbruch."
#define BROKEN_STREAM "Schreiben in Savegame-Datei fehlgeschlagen! Abbruch."



SaveGames::SaveGames( IrrlichtDevice* device )
: device_(device),
  fs_(0),
  savegameName_(""),
  CURRENT_VERSION(2)
{
    if ( device_ == 0 )
        Logfile::getInstance().emergencyExit( "Entchen in [SaveGames] nicht mehr gefunden! Abbruch.");
    fs_ = device_->getFileSystem();
    applicationDirectory_ = fs_->getWorkingDirectory();
    savegamesDirectory_ = applicationDirectory_ + "/SAVEGAMES";
    io::IFileList* dirTree = fs_->createFileList();
    if ( dirTree->findFile( savegamesDirectory_, true ) == -1 )
        Logfile::getInstance().emergencyExit( savegamesDirectory_ + " nicht gefunden! Abbruch." );
    dirTree->drop();
}



SaveGames::~SaveGames()
{
    // Niemals droppen, wenn Objekt nicht durch "create" erzeugt wurde!
}



void SaveGames::load( const io::path& filename )
{
    /**/Logfile& log = Logfile::getInstance();
    GenericHelperMethods::getInstance().validateFileExistence( filename );
    io::IReadFile* stream = fs_->createAndOpenFile( filename );
    checkVersion( read<u8>( stream ) );
    skip<u32>( stream ); // so far, timestamp is here of no interest
    /**/log.writeLine( Logfile::DEBUG, "hero: ", readString( stream ) );
    /**/log.writeLine( Logfile::DEBUG, "level: ", readString( stream ) );
    stream->drop();
}



const io::path& SaveGames::findNewest()
{
    fs_->changeWorkingDirectoryTo( savegamesDirectory_ );
    io::IFileList* fileList = fs_->createFileList();
    fs_->changeWorkingDirectoryTo( applicationDirectory_ );
    savegameName_ = "";
    io::IReadFile* stream = 0;
    u32 newestTimestamp = 0;
    for ( register u32 i = 0; i < fileList->getFileCount(); ++i )
    {
        if ( fileList->getFileName( i ).find( ".sav" ) == -1 )
            continue;
        const io::path& filename = fileList->getFullFileName( i );
        stream = fs_->createAndOpenFile( filename );
        if ( !stream )
        {
            Logfile::getInstance().writeLine( Logfile::INFO, "Lesen von Datei fehlgeschlagen: ", filename );
            continue;
        }
        checkVersion( read<u8>( stream ) );
        u32 timestamp = read<u32>( stream );
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


void SaveGames::save( const io::path& filename )
{
    io::IWriteFile* stream = fs_->createAndWriteFile( filename );
    if ( !stream )
    {
        Logfile::getInstance().writeLine( Logfile::INFO, "Savegame: ", filename);
        Logfile::getInstance().emergencyExit( BROKEN_STREAM );
    }
    write<u8>( stream, CURRENT_VERSION );
    write<u32>( stream, getTimestamp() );
    core::stringc heroData = "ONAMEder edle Testheld@OTYPEPUNK@MOFFS0.0x0.6x0.0@MROTA0.0x-90.0x0.0";
    heroData += "@MSCAL0.025x0.025x0.025@POSXZ11.0x11.0@MTEX0GFX/sydney.bmp@MFILEGFX/OBJECTS/sydney.md2";
    writeString( stream, heroData );
    writeString( stream, "Level_X" );
    stream->drop();
}



/* private */


// TODO File-Methoden auslagern nach eigener Klasse!
template <typename T> T SaveGames::read( io::IReadFile* stream )
{
    T buffer;
    u32 bytes = sizeof( typeof( buffer ) );
    if ( stream->read( &buffer, bytes ) < static_cast<s32>( bytes ) )
        Logfile::getInstance().emergencyExit( UNKNOWN_SAVEGAME_FORMAT );
    return buffer;
}



core::stringc SaveGames::readString( io::IReadFile* stream )
{
    u32 count = read<u32>( stream );
    u8* buffer = new u8[count];
    if ( stream->read( buffer, count ) < static_cast<s32>( count ) )
        Logfile::getInstance().emergencyExit( UNKNOWN_SAVEGAME_FORMAT );
    core::stringc ret = core::stringc( buffer );
    delete[] buffer;
    return ret;
}



template <typename T> void SaveGames::write( io::IWriteFile* stream, const T& number )
{
    if ( stream->write( &number, sizeof( T ) ) < static_cast<s32>( sizeof( T ) ) )
        Logfile::getInstance().emergencyExit( BROKEN_STREAM );
}
// explicit instantiations:
template void SaveGames::write<u8>( io::IWriteFile* stream, const u8& number );
template void SaveGames::write<u32>( io::IWriteFile* stream, const u32& number );



void SaveGames::writeString( io::IWriteFile* stream, const core::stringc& text )
{
    u32 count = text.size() + 1; // + 1 == trailing \0
    if ( stream->write( &count, sizeof( u32 ) ) < static_cast<s32>( sizeof( u32 ) ) )
        Logfile::getInstance().emergencyExit( BROKEN_STREAM );
    if ( stream->write( text.c_str(), count ) < static_cast<s32>( count ) )
        Logfile::getInstance().emergencyExit( BROKEN_STREAM );
}



template <typename T> void SaveGames::skip( io::IReadFile* stream )
{
    if ( !stream->seek( sizeof( T ), true ) )
        Logfile::getInstance().emergencyExit( UNKNOWN_SAVEGAME_FORMAT );
}
// explicit instantiations:
template void SaveGames::skip<u32>( io::IReadFile* stream );



void SaveGames::checkVersion( u8 version )
{
    // TODO create backward-compatibility later
    if ( version != CURRENT_VERSION )
    {
        core::stringc errorMessage = "Savegame-Version ";
        errorMessage += version;
        errorMessage += " unbekannt! Abbruch.";
        Logfile::getInstance().emergencyExit( errorMessage );
    }
}



u32 SaveGames::getTimestamp()
{
    /* get seconds elapsed since 1970-01-01 */
    ITimer::RealTimeDate datetime = device_->getTimer()->getRealTimeAndDate();
    if ( datetime.Year < 1970 )
        datetime.Year = 1970; // to avoid compatibility errors on systems with wrong date settings
    if ( datetime.IsDST )
        datetime.Hour--; // adjust hours of day with daylight saving time
    u32 m = ( datetime.Month + 9 ) % 12;
    s32 y = datetime.Year - m / 10;
    u32 days_since_1970 =
            y * 365 + y / 4 - y / 100 + y / 400
            + ( m * 306 + 5 ) / 10
            + datetime.Day - 1 // <-- days from 0000-01-01 until today
            - 719468; // days from 0000-01-01 until 1970-01-01
    return datetime.Second
        + datetime.Minute * 60
        + datetime.Hour * 3600 // BUG: #21, we have offset from GTM here!
        + days_since_1970 * 86400;
}
