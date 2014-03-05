/*! \file SaveGames.h
  \brief Klasse stellt Schnittstelle für Savegames bereit.
*/

#ifndef _SAVEGAMES_HEADER
#define _SAVEGAMES_HEADER

// Linken der IRRLICHT-DLL, nur in VisualStudio nötig
//#ifdef _IRR_WINDOWS_
//    #pragma comment(lib, "Irrlicht.lib")
//#endif

#include <irrlicht.h>

using namespace irr;
// Die innenliegenden Namespaces "core", "video" usw. werden im Folgenden
// immer explizit angegeben, um den Überblick zu behalten.

/*! \class SaveGames SaveGames.h "SaveGames.h"
  \brief Schnittstelle für Savegames.
  \note Instanzierung: `SaveGames* mySaveGames = new SaveGames();`
		\n Benutzen: `mySaveGames->load(...);`
*/
class SaveGames
{

public:

    /*! \brief Konstruktor.
      \param fs (\a io::IFileSystem*) Zeiger auf das Irrlicht-Dateisystem
      \return Zeiger auf das instanzierte Klassenobjekt
    */
    SaveGames( io::IFileSystem* fs );

	/*! \brief Destruktor
    */
	~SaveGames();

    /*! \brief Lädt ein Savegame.
      \param filename (\a u8*) Pfad und Dateiname des Savegames.
      \return -
    */
    void load( u8* filename );

    /*! \brief Findet das neueste Savegame.
      \param -
      \return \a io::path& Dateiname des neuesten Savegames, oder ""
    */
    const io::path& findNewest();

private:

    io::IFileSystem* fs_;
    io::path savegameName_;

    SaveGames( const SaveGames& );
    SaveGames& operator=( const SaveGames& );

};
// Ende class SaveGames

#endif
// Ende Header-Datei SaveGames
