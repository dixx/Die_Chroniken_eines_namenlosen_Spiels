#include "GameStateManager.h"

namespace leviathan
{
    namespace core
    {
        GameStateManager::GameStateManager()
        : states_(),
          runningStateIDs_()
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
            // TODO refactor!
            auto iter = runningStateIDs_.begin();
            auto size = runningStateIDs_.size();
            if ( 0 == size )
            {
                runningStateIDs_.push_front( id );
                return;
            }
            if ( *iter == id ) return;  // id is already on top of stack
            if ( size > 1 && *(iter + 1) == id )  // id is second on stack
            {
                runningStateIDs_.erase( iter );
            }
            else
            {
                for ( auto& it : runningStateIDs_ )
                {
                    if ( it == id ) return;
                }
                runningStateIDs_.push_front( id );
            }
        }

        void GameStateManager::update( const irr::f32 frameDeltaTime )
        {
            irr::u32 id = getActiveStateID();
            if ( id != 0xffffffff )
                ((GameState*)states_[id])->update( frameDeltaTime );
        }

        void GameStateManager::draw()
        {
            irr::u32 id = getActiveStateID();
            if ( id != 0xffffffff )
                ((GameState*)states_[id])->draw();
        }

        unsigned int GameStateManager::getGameStateCount()
        {
            return states_.size();
        }

        irr::u32 GameStateManager::getActiveStateID()
        {
            auto iter = runningStateIDs_.begin();
            return 0 == runningStateIDs_.size() ? 0xffffffff : *iter;
        }
    }
}
