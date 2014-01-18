#include "World.h"
#include "Camera.h"
#include "Ground.h"
//#include "Hero.h"
#include "Logfile.h"
#include "ObjectManager.h"
#include "Weather.h"



World& World::getInstance()
{
    static World _instance;
    return _instance;
}



void World::load( const World_ID world )
{
    core::stringc levelName;
    // todo Komplettieren!
    switch ( world )
    {
        case WORLD_FIRST:
            // Start-Karte zum Laden bereitstellen
            levelName = "GFX/LEVELS/Level_X";
            break;
        case WORLD_SAVEGAME:
            // Karte aus Speicherstand zum Laden bereitstellen
            Logfile::getInstance().writeLine( Logfile::DEBUG,
                    "Laden aus Speicherstand ist noch nicht implementiert." );
            break;
        default:
            Logfile::getInstance().writeLine( Logfile::DEBUG,
                    "Unzulaessiger Enumerator fuer Laden einer Welt: ", world );
            Logfile::getInstance().emergencyExit( ". Abbruch." );
            break;
    }
    Weather::getInstance().load();
    Ground::getInstance().load( ( levelName + ".map" ).c_str() );
    ObjectManager::getInstance().loadSolids( ( levelName + ".solids" ).c_str() );
    ObjectManager::getInstance().loadNPCs( ( levelName + ".npcs" ).c_str() );
    // ...initialisiere KI
//    Hero::getInstance().load();
//    Camera::getInstance().lockToNode( Hero::getInstance().getNode() );
}



void World::update( const f32 frameDeltaTime )
{
    Weather::getInstance().update();
    Ground::getInstance().update();
    ObjectManager::getInstance().update( frameDeltaTime );
//    Hero::getInstance().update( frameDeltaTime );
    Camera::getInstance().update( frameDeltaTime );
}



void World::unload()
{
    Camera::getInstance().lockToNode( 0 );
//    Hero::getInstance().unload();
    // ...fahre KI runter
    ObjectManager::getInstance().unload();
    Ground::getInstance().unload();
    Weather::getInstance().unload();
}



/* private */



World::World()
{
    // nothing to do here
}



World::~World()
{
    // Niemals droppen, wenn Objekt nicht durch "create" erzeugt wurde!
}
