#include "SaveGames.h"
#include "GenericHelperMethods.h"
#include "Logfile.h"

#define IS_FOLDER true
#define APPEND true



SaveGames::SaveGames( IrrlichtDevice* device )
: device_(device),
  fs_(0),
  savegameName_("")
{
    if ( device_ == 0 )
        Logfile::getInstance().emergencyExit(
                "Entchen in [SaveGames] nicht mehr gefunden! Abbruch.");
    fs_ = device_->getFileSystem();
    applicationDirectory_ = fs_->getWorkingDirectory();
    savegamesDirectory_ = applicationDirectory_ + "/SAVEGAMES";
    io::IFileList* dirTree = fs_->createFileList();
    if ( dirTree->findFile( savegamesDirectory_, IS_FOLDER ) == -1 )
        Logfile::getInstance().emergencyExit(
                savegamesDirectory_ + " nicht gefunden! Abbruch." );
    dirTree->drop();
}



SaveGames::~SaveGames()
{
    // Niemals droppen, wenn Objekt nicht durch "create" erzeugt wurde!
}



void SaveGames::load( const io::path& filename )
{
    Logfile& log = Logfile::getInstance();
    GenericHelperMethods::getInstance().validateFileExistence( filename );
    io::IReadFile* stream = fs_->createAndOpenFile( filename );
    u8 version = read<u8>( stream );
    if ( version != 1 )
    {
        log.write( Logfile::DEBUG, "Savegame-Version ", version );
        log.emergencyExit( " unbekannt! Abbruch." );
    }
    //
    skip<u32>( stream );
    log.writeLine( Logfile::DEBUG, "hero: ", readString( stream ) );
    log.writeLine( Logfile::DEBUG, "level: ", readString( stream ) );
    //
    stream->drop();
}



const io::path& SaveGames::findNewest()
{
    savegameName_ = "";
    io::IReadFile* stream = 0;
    u32 lastTimestamp = 0;
    u8 version = 0;
    u32 timestamp = 0;
    fs_->changeWorkingDirectoryTo( savegamesDirectory_ );
    io::IFileList* dirTree = fs_->createFileList();
    fs_->changeWorkingDirectoryTo( applicationDirectory_ );
    for ( register u32 i = 0; i < dirTree->getFileCount(); ++i )
    {
        if ( dirTree->getFileName( i ).find( ".sav" ) != -1 )
        {
            /**/save( dirTree->getFullFileName( i ) );
            stream = fs_->createAndOpenFile( dirTree->getFullFileName( i ) );
            version = read<u8>( stream );
            if ( version != 1 )
            {
                Logfile::getInstance().write( Logfile::DEBUG,
                        "Savegame-Version ", version );
                Logfile::getInstance().emergencyExit( " unbekannt! Abbruch." );
            }
            timestamp = read<u32>( stream );
            if ( timestamp > lastTimestamp )
            {
                savegameName_ = dirTree->getFullFileName( i );
                lastTimestamp = timestamp;
            }
            stream->drop();
        }
    }
    dirTree->drop();
    /**/if ( !savegameName_.empty() ) load( savegameName_ );
    return savegameName_;
}

// TODO on successful character creation, create one savegame, clone the other two from it.


void SaveGames::save( const io::path& filename )
{
    io::IWriteFile* stream = fs_->createAndWriteFile( filename, false );
    if ( !stream )
    {
        Logfile::getInstance().write( Logfile::INFO, "Savegame ", filename);
        Logfile::getInstance().emergencyExit(
                " konnte nicht geschrieben werden! Abbruch." );
    }
    write<u8>( stream, 1 ); // version
    write<u32>( stream, device_->getTimer()->getRealTime() ); // TODO fix bug!
    writeString( stream, "ONAMEder edle Testheld@OTYPEPUNK" );
    writeString( stream, "Level_X" );
    stream->drop();
}



/* private */



template <typename T> T SaveGames::read( io::IReadFile* stream )
{
    T buffer;
    u32 bytes = sizeof( typeof( buffer ) );
    if ( stream->read( &buffer, bytes ) < static_cast<s32>( bytes ) )
        Logfile::getInstance().emergencyExit(
                "Unbekanntes Savegame-Format! Abbruch." );
    return buffer;
}



core::stringc SaveGames::readString( io::IReadFile* stream )
{
    u32 count = read<u32>( stream );
    u8* buffer = new u8[count];
    if ( stream->read( buffer, count ) < static_cast<s32>( count ) )
        Logfile::getInstance().emergencyExit(
                "Unbekanntes Savegame-Format! Abbruch." );
    core::stringc ret = core::stringc( buffer );
    delete[] buffer;
    return ret;
}



template <typename T> void SaveGames::write( io::IWriteFile* stream,
        const T& number )
{
    stream->write( &number, sizeof( T ) );
}
// explicit instantiations:
template void SaveGames::write<u8>( io::IWriteFile* stream, const u8& number );
template void SaveGames::write<u32>( io::IWriteFile* stream, const u32& number );



void SaveGames::writeString( io::IWriteFile* stream, const core::stringc& text )
{
    u32 count = text.size() + 1; // + 1 == trailing \0
    stream->write( &count, sizeof( u32 ) );
    stream->write( text.c_str(), count );
}



template <typename T> void SaveGames::skip( io::IReadFile* stream )
{
    stream->seek( sizeof( T ), true );
}
// explicit instantiations:
template void SaveGames::skip<u32>( io::IReadFile* stream );
