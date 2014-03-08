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
    savegameName_ = "";
    u32 lastTimestamp = 0;
    u32 version = 0;
    u32 timestamp = 0;
    io::path applicationDirectory = fs_->getWorkingDirectory();
    io::path savegamesDirectory = applicationDirectory + "/SAVEGAMES";
    io::IFileList* dirTree = fs_->createFileList();
    if ( dirTree->findFile( savegamesDirectory, IS_FOLDER ) == -1 )
        Logfile::getInstance().emergencyExit(
                savegamesDirectory + " nicht gefunden! Abbruch." );
    dirTree->drop();
    fs_->changeWorkingDirectoryTo( savegamesDirectory );
    dirTree = fs_->createFileList();
    fs_->changeWorkingDirectoryTo( applicationDirectory );
    for ( register u32 i = 0; i < dirTree->getFileCount(); ++i )
    {
        if ( dirTree->getFileName( i ).find( ".sav" ) != -1 )
        {
            write( dirTree->getFullFileName( i ) );
            io::IReadFile* savegame = fs_->createAndOpenFile(
                    dirTree->getFullFileName( i ) );
            if ( savegame->read( &version, 1 ) < 1 )
                Logfile::getInstance().emergencyExit(
                        "Unbekanntes Savegame-Format! Abbruch." );
            if ( version != 1 )
            {
                Logfile::getInstance().write( Logfile::DEBUG,
                        "Savegame-Version ", version );
                Logfile::getInstance().emergencyExit(
                        " unbekannt! Abbruch." );
            }
            if ( savegame->read( &timestamp, 4 ) < 4 )
                Logfile::getInstance().emergencyExit(
                        "Unbekanntes Savegame-Format! Abbruch." );
            if ( timestamp > lastTimestamp )
                savegameName_ = dirTree->getFullFileName( i );
            savegame->drop();
        }
    }
    dirTree->drop();
    Logfile::getInstance().writeLine( Logfile::DEBUG, "savegame found: ",
            savegameName_ );
    return savegameName_;
}

// TODO on successful character creation, create one savegame, clone the other two from it.


void SaveGames::write( const io::path& filename )
{
    io::IWriteFile* savegame = fs_->createAndWriteFile( filename );
    u8 version = 1;
    savegame->write( &version, 1 );
    u32 timestamp = device_->getTimer()->getRealTime();
    savegame->write( &timestamp, 4 );
    savegame->drop();
}



/* private */
