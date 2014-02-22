#include "GameStateManager.h"
#include "Logfile.h"
#include "StateLoadGameContent.h"
#include "StatePlayTheGame.h"
#include "StateStartup.h"
#include "StateUnloadGameContent.h"
#include "StateMainMenu.h"



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
            switchState();
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



bool GameStateManager::handleGuiEvents( const irr::SEvent& event )
{
    if ( currentState_ )
        return currentState_->handleGuiEvents( event );
    else
        return false;
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
        case LOAD:
            validateRequestForLoad();
            break;
        case GAME:
            validateRequestForGame();
            break;
        case UNLOAD:
            validateRequestForUnload();
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
            currentState_ = new StateMainMenu( device_ );
            break;
        case LOAD:
            currentState_ = new StateLoadGameContent( device_ );
            break;
        case GAME:
            currentState_ = new StatePlayTheGame( device_ );
            break;
        case UNLOAD:
            currentState_ = new StateUnloadGameContent( device_ );
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
        case UNLOAD:
            requestedState_ = MAIN_MENU;
            break;
        default:
            Logfile::getInstance().emergencyExit(
                    "Unzulässige Anforderung von GameState MAIN_MENU! Abbruch."
            );
            break;
    }
}



void GameStateManager::validateRequestForLoad()
{
    switch ( runningState_ )
    {
        case MAIN_MENU:
            requestedState_ = LOAD;
            break;
        default:
            Logfile::getInstance().emergencyExit(
                    "Unzulässige Anforderung von GameState LOAD! Abbruch." );
            break;
    }
}



void GameStateManager::validateRequestForGame()
{
    switch ( runningState_ )
    {
        case LOAD:
            requestedState_ = GAME;
            break;
        default:
            Logfile::getInstance().emergencyExit(
                    "Unzulässige Anforderung von GameState GAME! Abbruch." );
            break;
    }
}



void GameStateManager::validateRequestForUnload()
{
    switch ( runningState_ )
    {
        case GAME:
            requestedState_ = UNLOAD;
            break;
        default:
            Logfile::getInstance().emergencyExit(
                    "Unzulässige Anforderung von GameState UNLOAD! Abbruch." );
            break;
    }
}



void GameStateManager::unknownStateRequested()
{
    Logfile::getInstance().emergencyExit(
            "Unbekannter GameState angefordert! Abbruch." );
}
