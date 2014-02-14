#include "StatePlayTheGame.h"
#include "Eventreceiver.h"
#include "GameStateManager.h"
#include "Logfile.h"
#include "Mauspfeil.h"
#ifdef _DEBUG_MODE
#include "Debugwindow.h"
#endif


StatePlayTheGame::StatePlayTheGame( IrrlichtDevice* device )
: GameState(),
  device_(device)
{
    if ( device_ == 0 )
        Logfile::getInstance().emergencyExit(
                "Entchen in [StatePlayTheGame] nicht mehr gefunden! Abbruch." );
    device_->setWindowCaption( L"Die Chroniken eines namenlosen Spiels" );
    transitTo( STARTING );
}



StatePlayTheGame::~StatePlayTheGame()
{
    // Niemals droppen, wenn Objekt nicht durch "create" erzeugt wurde!
}



void StatePlayTheGame::start( f32 frameDeltaTime )
{
    transitTo( RUNNING );
#pragma GCC diagnostic ignored "-Wunused-parameter" // ==> frameDeltaTime
}
#pragma GCC diagnostic error "-Wunused-parameter"



void StatePlayTheGame::update( f32 frameDeltaTime )
{
    GameStateManager::getInstance().requestNewState( GameStateManager::UNLOAD );
    transitTo( STOPPING );
#pragma GCC diagnostic ignored "-Wunused-parameter" // ==> frameDeltaTime
}
#pragma GCC diagnostic error "-Wunused-parameter"



void StatePlayTheGame::shutdown( f32 frameDeltaTime )
{
    transitTo( STOPPED );
#pragma GCC diagnostic ignored "-Wunused-parameter" // ==> frameDeltaTime
}
#pragma GCC diagnostic error "-Wunused-parameter"



void StatePlayTheGame::draw()
{
    device_->getVideoDriver()->beginScene();
    device_->getSceneManager()->drawAll();
    device_->getGUIEnvironment()->drawAll();
#ifdef _DEBUG_MODE
    Debugwindow::getInstance().show();
#endif
    Mauspfeil::getInstance().draw();
    device_->getVideoDriver()->endScene();
}



bool StatePlayTheGame::handleGuiEvents( const irr::SEvent& event )
{
#pragma GCC diagnostic ignored "-Wunused-parameter" // ==> event
    return false;
}
#pragma GCC diagnostic error "-Wunused-parameter"



/* private */



void StatePlayTheGame::transitTo( internalState state )
{
    switch ( state )
    {
        case STARTING:
            currentInternalState_ = STARTING;
            break;
        case RUNNING:
            currentInternalState_ = RUNNING;
            Eventreceiver::getInstance().setEventReactionActive(
                    true, true, true );
            Mauspfeil::getInstance().setCurrentArrow(
                    Mauspfeil::MAUSPFEIL_SELECT );
            break;
        case STOPPING:
            currentInternalState_ = STOPPING;
            break;
        default:
            currentInternalState_ = STOPPED;
            break;
    }
}
