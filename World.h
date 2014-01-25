/*! \file World.h
  \brief Klasse (Singleton) stellt Schnittstelle für eine Spielewelt bereit.
*/

#ifndef _WORLD_HEADER
#define _WORLD_HEADER

// Linken der IRRLICHT-DLL, nur in VisualStudio nötig
//#ifdef _IRR_WINDOWS_
//    #pragma comment(lib, "Irrlicht.lib")
//#endif

#include <irrlicht.h>

using namespace irr;
// Die innenliegenden Namespaces "core", "video" usw. werden im Folgenden
// immer explizit angegeben, um den Überblick zu behalten.

/*! \class World World.h "World.h"
  \brief Schnittstelle für eine Spielewelt.
  \attention Klasse ist `Singleton`.
  \note Instanzierung: `World& myWorld = World::getInstance();`
        \n Oder: `World::getInstance();`
        \n Benutzen: `myWorld.load(WORLD_SAVEGAME);`
        \n Oder: `World::getInstance().unload();`
*/
class World
{

public:

    /*! \brief Jede Welt erhält eine ID.
    */
    enum World_ID
    {
        WORLD_FIRST = 0,  //!< Spielstart
        WORLD_SAVEGAME,  //!< aus Speicherstand laden

        WORLD_COUNT  //!< Anzahl verfügbarer IDs, sicherheitsrelevant!
    };

    /*! \brief Ersatz für den Konstruktor.

      Instanziert die Klasse einmalig und verhindert Mehrfachinstanzierung.
      \param -
      \return Referenz auf die einzige Instanz dieser Klasse
    */
    static World& getInstance();

    /*! \brief Lädt eine Spielewelt.
      \param world (\a World_ID) ID der zu ladenden Welt
      \return -
    */
    void load( const World_ID world );

    /*! \brief Updatet alles was zur Welt gehört.
      \param frameDeltaTime (\a const \a f32) Dauer des letzten Frames in
             Sekunden
      \return -
    */
    void update( const f32 frameDeltaTime );

    /*! \brief Entlaedt die aktuelle Spielewelt. Objekte werden zerstoert und
    //!        Speicher wird freigegeben.
    //! \param -
    //! \return -
    */
    void unload();

private:

    World();  // ctor. Von aussen keine Instanzen direkt erzeugbar
    World( const World& );  // Instanz ist nicht kopierbar
    World& operator=( const World& );  // Instanz ist nicht zuweisbar
    ~World();  // dtor. Instanz zerstoert sich bei Programmende

};
// Ende class World

#endif
// Ende Header-Datei World
