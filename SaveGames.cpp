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
    GenericHelperMethods::getInstance().validateFileExistence( filename );
}



const io::path& SaveGames::findNewest()
{
    Logfile& log = Logfile::getInstance();
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
            /**/write( dirTree->getFullFileName( i ) );
            stream = fs_->createAndOpenFile( dirTree->getFullFileName( i ) );
            version = read<u8>( stream );
            if ( version != 1 )
            {
                log.write( Logfile::DEBUG, "Savegame-Version ", version );
                log.emergencyExit( " unbekannt! Abbruch." );
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
    log.writeLine( Logfile::DEBUG, "savegame found: ", savegameName_ );
    return savegameName_;
}

// TODO on successful character creation, create one savegame, clone the other two from it.


void SaveGames::write( const io::path& filename )
{
    io::IWriteFile* savegame = fs_->createAndWriteFile( filename );
    u8 version = 1;
    savegame->write( &version, sizeof( u8 ) );
    u32 timestamp = device_->getTimer()->getRealTime();
    savegame->write( &timestamp, sizeof( u32 ) );
    savegame->drop();
}



/* private */



template <typename T>
T SaveGames::read( io::IReadFile* stream )
{
    T buffer = 0;
    u32 bytes = sizeof( typeof( buffer ) );
    if ( stream->read( &buffer, bytes ) < static_cast<s32>( bytes ) )
        Logfile::getInstance().emergencyExit(
                "Unbekanntes Savegame-Format! Abbruch." );
    return buffer;
}
