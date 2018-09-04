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

        void GameStateManager::add(GameState& gameState, uint32_t id)
        {
            states_[id] = &gameState;
        }

        void GameStateManager::transitTo(uint32_t id)
        {
            if (runningStateIDs_.empty())
            {
                runningStateIDs_.push_front(id);
                return;
            }
            if (runningStateIDs_.front() == id) return;  // id is already on top of stack
            if (runningStateIDs_.size() > 1 && *std::next(runningStateIDs_.begin()) == id)  // id is second on stack
            {
                runningStateIDs_.pop_front();
            }
            else
            {
                for (auto& item : runningStateIDs_)
                {
                    if (item == id) return;
                }
                runningStateIDs_.push_front(id);
            }
        }

        void GameStateManager::update(const float elapsedSeconds)
        {
            uint32_t id = getActiveStateID();
            if (id != 0xffffffff)
                states_[id]->update(elapsedSeconds);
        }

        void GameStateManager::draw()
        {
            uint32_t id = getActiveStateID();
            if (id != 0xffffffff)
                states_[id]->draw();
        }

        size_t GameStateManager::getGameStateCount()
        {
            return states_.size();
        }

        uint32_t GameStateManager::getActiveStateID()
        {
            return runningStateIDs_.empty() ? 0xffffffff : runningStateIDs_.front();
        }
    }
}
