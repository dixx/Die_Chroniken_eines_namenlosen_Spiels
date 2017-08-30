#include "GameStateManager.h"
#include <iterator>

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

        void GameStateManager::add( GameState& gameState, uint32_t id )
        {
            states_[id] = &gameState;
        }

        void GameStateManager::transitTo( uint32_t id )
        {
            auto size = runningStateIDs_.size();
            if ( 0 == size )
            {
                runningStateIDs_.push_front( id );
                return;
            }
            if ( runningStateIDs_.front() == id ) return;  // id is already on top of stack
            if ( size > 1 && *std::next( runningStateIDs_.begin() ) == id )  // id is second on stack
            {
                runningStateIDs_.pop_front();
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

        void GameStateManager::update( const float elapsedSeconds )
        {
            uint32_t id = getActiveStateID();
            if ( id != 0xffffffff )
                states_[id]->update( elapsedSeconds );
        }

        void GameStateManager::draw()
        {
            uint32_t id = getActiveStateID();
            if ( id != 0xffffffff )
                states_[id]->draw();
        }

        unsigned int GameStateManager::getGameStateCount()
        {
            return states_.size();
        }

        uint32_t GameStateManager::getActiveStateID()
        {
            return 0 == runningStateIDs_.size() ? 0xffffffff : runningStateIDs_.front();
        }
    }
}
