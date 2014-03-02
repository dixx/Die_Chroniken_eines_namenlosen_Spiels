#include "SaveGames.h"
#include "GenericHelperMethods.h"
#include "Logfile.h"



SaveGames::SaveGames( io::IFileSystem* fs )
: fs_(fs)
{
    if ( fs_ == 0 )
        Logfile::getInstance().emergencyExit(
                "Dateisystem in [SaveGames] nicht mehr gefunden! Abbruch.");
}



SaveGames::~SaveGames()
{
    // Niemals droppen, wenn Objekt nicht durch "create" erzeugt wurde!
}



void SaveGames::load( u8* filename )
{
    GenericHelperMethods::getInstance().validateFileExistence( filename );
}



void SaveGames::loadNewest()
{
    io::path applicationDirectory = fs_->getWorkingDirectory();
    io::path savegamesDirectory = applicationDirectory + "/SAVEGAMES";
    io::IFileList* dirTree = fs_->createFileList();
    s32 index = dirTree->findFile( savegamesDirectory, true );
    if ( index == -1 )
    {
        Logfile::getInstance().emergencyExit(
                "Ordner SAVEGAMES nicht gefunden! Abbruch.");
        // create folder, create one savegame, clone the other two from it.
    }
    dirTree->drop();
    fs_->changeWorkingDirectoryTo( savegamesDirectory );
    dirTree = fs_->createFileList();
    fs_->changeWorkingDirectoryTo( applicationDirectory );
    for ( register u32 i = 0; i < dirTree->getFileCount(); ++i)
        Logfile::getInstance().writeLine( Logfile::DEBUG,
                dirTree->getFullFileName( i ) );
    dirTree->drop();
}



/* private */
