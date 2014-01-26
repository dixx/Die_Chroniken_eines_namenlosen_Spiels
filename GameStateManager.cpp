#include "GameStateManager.h"
#include "Logfile.h"
#include "StateStartup.h"
#include "StateMainMenue.h"



GameStateManager& GameStateManager::getInstance( IrrlichtDevice* device )
{
    static GameStateManager _instance( device );
    return _instance;
}



void GameStateManager::update( f32 frameDeltaTime )
{
    switch ( currentState_->currentInternalState() ) // ordered by propability
    {
        case GameState::RUNNING:
            currentState_->update( frameDeltaTime );
            break;
        case GameState::STARTING:
            currentState_->start( frameDeltaTime );
            break;
        case GameState::STOPPED:
            switchState(); // POTENTIALBUG we loose one frame of drawing here.
            break;
        default:
            currentState_->shutdown( frameDeltaTime );
            break;
    }
}



void GameStateManager::draw()
{
    if ( currentState_ )
        currentState_->draw();
}



void GameStateManager::requestNewState( State desiredState )
{
    switch ( desiredState )
    {
        case STARTUP:
            validateRequestForStartup();
            break;
        case MAIN_MENU:
            validateRequestForMainMenu();
            break;
        case SHUTDOWN:
            requestedState_ = SHUTDOWN;  // Anfrage von SHUTDOWN ist immer zulässig.
            break;
        default:
            unknownStateRequested();
            break;
    }
}



/* private */



GameStateManager::GameStateManager( IrrlichtDevice* device )
: device_(device),
  currentState_(0),
  requestedState_(NOSTATE),
  runningState_(NOSTATE)
{
    if ( device_ == 0 )
        Logfile::getInstance().emergencyExit(
                "Entchen in [GameStateManager] nicht mehr gefunden! Abbruch." );
    requestNewState( STARTUP );
    switchState();
}



GameStateManager::~GameStateManager()
{
    // Niemals droppen, wenn Objekt nicht durch "create" erzeugt wurde!
    if ( currentState_)
        delete currentState_;
    currentState_ = 0;
    device_ = 0;
}



void GameStateManager::switchState()
{
    if ( currentState_ )
        delete currentState_;
    switch ( requestedState_ )
    {
        case STARTUP:
            currentState_ = new StateStartup( device_ );
            break;
        case MAIN_MENU:
            currentState_ = new StateMainMenue( device_ );
            break;
        default: // SHUTDOWN
            device_->closeDevice(); // create GameState Shutdown later
            currentState_ = 0;
            break;
    }
    runningState_ = requestedState_;
}



void GameStateManager::validateRequestForStartup()
{
    switch ( runningState_ )
    {
        case NOSTATE:
            requestedState_ = STARTUP;
            break;
        default:
            Logfile::getInstance().emergencyExit(
                    "Unzulässige Anforderung von GameState STARTUP! Abbruch." );
            break;
    }
}



void GameStateManager::validateRequestForMainMenu()
{
    switch ( runningState_ )
    {
        case STARTUP:
            requestedState_ = MAIN_MENU;
            break;
        default:
            Logfile::getInstance().emergencyExit(
                    "Unzulässige Anforderung von GameState MAIN_MENU! Abbruch."
            );
            break;
    }
}



void GameStateManager::unknownStateRequested()
{
    Logfile::getInstance().emergencyExit(
            "Unbekannter GameState angefordert! Abbruch." );
}
