#include "GameStateManager.h"
#include "Logfile.h"
#include "StateStartup.h"



GameStateManager& GameStateManager::getInstance( IrrlichtDevice* device )
{
    static GameStateManager _instance( device );
    return _instance;
}



GameState* GameStateManager::getActiveState()
{
    return currentState_;
}



/* private */



GameStateManager::GameStateManager( IrrlichtDevice* device )
: device_(device)
{
    if ( device_ == 0 )
        Logfile::getInstance().emergencyExit(
                "Entchen in [GameStateManager] nicht mehr gefunden! Abbruch." );
	states_.reallocate( STATES_COUNT );
    states_[ STARTUP ] = new StateStartup( device_ );
    //states_[ MAIN_MENU ] = new GameState();
    //states_[ GAME ] = new GameState();
	currentState_ = states_[ STARTUP ];
	// todo check if a state does really NOT need a start and end method!
}



GameStateManager::~GameStateManager()
{
    // Niemals droppen, wenn Objekt nicht durch "create" erzeugt wurde!
    currentState_ = 0;
    for ( register u32 i = 0; i < 1; ++i)//states_.size(); ++i )
        delete states_[ i ];
    device_ = 0;
}
