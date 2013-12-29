#include "StateStartup.h"
//#include "Camera.h"
//#include "Collision.h"
//#include "Eventreceiver.h"
//#include "GenericHelperMethods.h"
//#include "Ground.h"
//#include "Hero.h"
//#include "Logfile.h"
//#include "Mauspfeil.h"
//#include "ObjectManager.h"
//#include "Scripting.h"
//#include "TimerManager.h"
//#include "Ton.h"
//#include "Weather.h"
//#include "World.h"
//#include "Zufall.h"
#ifdef _DEBUG_MODE
//#include "DebugShapesManager.h"
//#include "Debugwindow.h"
#endif



StateStartup::StateStartup( IrrlichtDevice* device)
: GameState()
{
    // mebbe use an enum "loading order"?
    draw();
//#ifdef _DEBUG_MODE
//    DebugShapesManager::getInstance( driver );
//    Debugwindow::getInstance( device );
//#endif
//    draw();
//    GenericHelperMethods::getInstance( device );
//    draw();
//    TimerManager::getInstance();
//    draw();
//    Scripting::getInstance();
//    draw();
//    ObjectManager::getInstance( device );
//    draw();
//    Collision::getInstance( scenemanager );
//    draw();
//    Ton::getInstance( filesystem );
//    draw();
//    Mauspfeil::getInstance( device );
//    draw();
//    Weather::getInstance( scenemanager );
//    draw();
//    Ground::getInstance( device );
//    draw();
//    Camera::getInstance( scenemanager );
//    draw();
//    Hero::getInstance( scenemanager );
//    draw();
//    World::getInstance();
//    draw();
//    Zufall::getInstance().start( device->getTimer()->getRealTime() );
    //Menues::getInstance( device );
    // ...
    //Menues::getInstance().transitTo( Menues::MENUE_HAUPTMENUE );
}



StateStartup::~StateStartup()
{
    // Niemals droppen, wenn Objekt nicht durch "create" erzeugt wurde!
}



void StateStartup::update( f32 frameDeltaTime )
{
    frameDeltaTime += 1.0f;
}



void StateStartup::draw()
{

}



bool StateStartup::handleGuiEvents()
{
    return false;
}



/* private */
