#include "GameStateManager.h"
#include <iterator>
#include <stdexcept>

namespace leviathan {
    namespace core {
        void GameStateManager::add(IGameState& gameState, uint32_t id) {
            if (id == NO_STATE_ACTIVE)
                throw std::invalid_argument("0xffffffff is the only value not allowed as an ID here, sorry!");
            states_[id] = &gameState;
        }

        void GameStateManager::transitTo(uint32_t id) {
            if (states_.find(id) == states_.end())
                return;
            if (getActiveStateID() == NO_STATE_ACTIVE) {
                runningStateIDs_.push_front(id);
            } else if (runningStateIDs_.size() > 1 && *std::next(runningStateIDs_.begin()) == id) {
                runningStateIDs_.pop_front();  // id is second on stack
            } else {
                for (auto& item : runningStateIDs_) {
                    if (item == id)
                        return;
                }
                runningStateIDs_.push_front(id);
            }
        }

        void GameStateManager::update(const float elapsedSeconds) {
            uint32_t id = getActiveStateID();
            if (id != NO_STATE_ACTIVE)
                states_[id]->update(elapsedSeconds);
        }

        void GameStateManager::draw() {
            uint32_t id = getActiveStateID();
            if (id != NO_STATE_ACTIVE)
                states_[id]->draw();
        }

        size_t GameStateManager::getGameStateCount() const {
            return states_.size();
        }

        uint32_t GameStateManager::getActiveStateID() {
            return runningStateIDs_.empty() ? NO_STATE_ACTIVE : runningStateIDs_.front();
        }
    }
}
