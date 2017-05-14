#include "GameStateManager.h"

namespace leviathan
{
    namespace core
    {
        GameStateManager::GameStateManager()
        : states_(),
          runningStates_()
        {
        }

        GameStateManager::~GameStateManager()
        {
        }

        void GameStateManager::add( GameState& gameState, irr::u32 id )
        {
            states_.insert( id, &gameState );
        }

        void GameStateManager::transitTo( irr::u32 id )
        {
            (void)id;
        }

        void GameStateManager::update( const irr::f32 frameDeltaTime )
        {
            (void)frameDeltaTime;
        }

        void GameStateManager::draw()
        {
            ;
        }

        unsigned int GameStateManager::getGameStateCount()
        {
            return states_.size();
        }

        irr::u32 GameStateManager::getActiveStateID()
        {
            return 0;
        }
    }
}
