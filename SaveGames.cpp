#include "SaveGames.h"
#include "GenericHelperMethods.h"
#include "Logfile.h"

#define IS_FOLDER true



SaveGames::SaveGames( io::IFileSystem* fs )
: fs_(fs),
  savegameName_("")
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



const io::path& SaveGames::findNewest()
{
    savegameName_ = "";
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
            Logfile::getInstance().writeLine(
                    Logfile::DEBUG,
                    "savegame found: ",
                    dirTree->getFullFileName( i )
            );
        }
    }
    dirTree->drop();
    return savegameName_;
}

// TODO on successful character creation, create one savegame, clone the other two from it.

/* private */
