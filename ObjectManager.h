/*! \file ObjectManager.h
  \brief Klasse (Singleton) stellt Schnittstelle für alle Objekte bereit.
*/

#ifndef _OBJECTMANAGER_HEADER
#define _OBJECTMANAGER_HEADER

#include "Basic3DObject.h"
#include "BasicLifeform.h"
#include "BasicStaticObject.h"
#include "Timer.h"
#include "Vegetation.h"

/*! \class ObjectManager ObjectManager.h "ObjectManager.h"
  \brief  Schnittstelle für 3D-Objekte (meist Szenenknoten).
  \attention Klasse ist `Singleton`.
  \note Instanzierung: `ObjectManager& myObjectManager =
        ObjectManager::getInstance();`
        \n Oder: `ObjectManager::getInstance();`
        \n Benutzen: `myObjectManager.load("test.solids");`
        \n Oder: `ObjectManager::getInstance().update();`
*/
class ObjectManager
{

public:

    //! @name Knoten-Hierarchie, nach Zweck geordnet.
    //! @{

    //! die Welt
    scene::ISceneNode* worldNode;
        //! Knoten die auf den Mauspfeil reagieren
        scene::ISceneNode* nodesRespondingToMouse;
            //! begehbare Knoten
            scene::ISceneNode* walkableNodes;
                //! begehbare Knoten in Sichtradius des Heldens
                scene::ISceneNode* walkableNodesInRange;
            //! Leichen
            scene::ISceneNode* corpseNodes;
            //! Lebensformen-Knoten
            scene::ISceneNode* lifeformNodes;
            //! Inventar-Knoten
            scene::ISceneNode* inventoryNodes;
            //! klickbare und kollidierbare Knoten
            scene::ISceneNode* interactiveNodes;
        //! Knoten die nur kollidierbar sind
        scene::ISceneNode* obstacleNodes;
        //! Knoten ohne Kollisionserkennung
        scene::ISceneNode* decorativeNodes;
            //! Wetter-Knoten
            scene::ISceneNode* weatherNodes;
        //! Geschosse-Knoten
        scene::ISceneNode* bulletNodes;

    //! @}

    /*! \brief Ersatz für den Konstruktor.

      Instanziert die Klasse einmalig und verhindert Mehrfachinstanzierung.
      \param device (\a IrrlichtDevice*) Zeiger auf das Entchen
      \return Referenz auf die einzige Instanz dieser Klasse
    */
    static ObjectManager& getInstance( IrrlichtDevice* device = 0 );

    /*! \brief Lade alle unbewegten Objekte.
      \param solidsFilename (\a const \a char*) Dateiname der statischen
             Objekte
      \return -
    */
    void loadSolids( const char* solidsFilename );

    /*! \brief Lade alle NPCs.
      \param npcsFilename (\a const \a char*) Dateiname der NPCs
      \return -
    */
    void loadNPCs( const char* npcsFilename );

    /*! \brief Entlädt alle Objekte.
      \param -
      \return -
    */
    void unload();

    /*! \brief Macht Objekte sichtbar oder unsichtbar.
      \param frameDeltaTime (\a const \a f32) Zeit zwischen zwei Frames
      \return -
    */
    void update( const f32 frameDeltaTime );

    /*! \brief Gibt den Basisknoten für den entsprechenden Typ zurück.
      \param type (\a const\a core::stringc&) Objekttyp
      \return \a scene::ISceneNode* Basisknoten
    */
    scene::ISceneNode* getBaseNodeByType( const core::stringc& type );

    /*! \brief Gibt die Basis-ID inklusive Flags für den entsprechenden Typ
               zurück.
      \param type (\a const\a core::stringc&) Objekttyp
      \return \a u32 Basis-ID mit Flags
    */
    u32 getBaseIdByType( const core::stringc& type );

    /*! \brief Macht Objekt sichtbar und fügt es zur Kollisionserkennung hinzu.
      \param object (\a Basic3DObject*) Zeiger auf das Objekt
      \return -
    */
    void addObjectToAreaOfView(Basic3DObject* object);

    /*! \brief Macht Objekt unsichtbar und entfernt es aus der Kollisions-
               erkennung.
      \param object (\a Basic3DObject*) Zeiger auf das Objekt
      \return -
    */
    void removeObjectFromAreaOfView(Basic3DObject* object);

#ifdef _DEBUG_MODE
    void switchStaticsDebugMode();
    void switchNPCsDebugMode();
    u32 loadedNodes();
#endif

private:

    // todo refactor usage of device here! mebbe invent a new timer?
    IrrlichtDevice* device_; // only needed by debug timing. duh.
    scene::ISceneManager* smgr_;
    core::array<BasicStaticObject*> staticObjects_;
    core::array<BasicLifeform*> npcs_;
    Vegetation* vegetation_;
    Timer* updateTimer_;
#ifdef _DEBUG_MODE
    u32 visibleNodeCount_;
    u32 debugCounter_;
#endif

    ObjectManager( IrrlichtDevice* device );
    ObjectManager( const ObjectManager& );
    ObjectManager& operator=( const ObjectManager& );
    ~ObjectManager();

    void clearArrays();

};
// Ende class ObjectManager

#endif
// Ende Header-Datei ObjectManager
