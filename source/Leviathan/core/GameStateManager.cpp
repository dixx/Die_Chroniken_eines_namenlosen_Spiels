#include "GameStateManager.h"
#include <iterator>
#include <stdexcept>

namespace leviathan {
    namespace core {
        void GameStateManager::add(IGameState& gameState, uint32_t id) {
            if (id == NO_STATE_ACTIVE)
                throw std::invalid_argument("0xffffffff is not allowed as an ID here, sorry!");
            if (states_.find(id) == states_.end()) {
                states_[id] = &gameState;
            } else {
                // TODO: log it!
            }
        }

        void GameStateManager::transitTo(uint32_t id) {
            if (states_.find(id) == states_.end())  // no such state
                return;  // TODO: log it!
            if (runningStateIDs_.empty()) {
                runningStateIDs_.push_front(id);
                return;
            }
            if (runningStateIDs_.front() == id)  // id is already on top of stack
                return;  // TODO: log it!
            if (runningStateIDs_.size() > 1 && *std::next(runningStateIDs_.begin()) == id) {  // id is second on stack
                runningStateIDs_.pop_front();
            } else {
                for (auto& item : runningStateIDs_) {
                    if (item == id)
                        return;  // TODO: log it!
                }
                runningStateIDs_.push_front(id);
            }
        }

        void GameStateManager::update(const float elapsedSeconds) {
            uint32_t id = getActiveStateID();
            if (id == NO_STATE_ACTIVE)
                return;
            states_[id]->update(elapsedSeconds);
        }

        void GameStateManager::draw() {
            uint32_t id = getActiveStateID();
            if (id == NO_STATE_ACTIVE)
                return;
            states_[id]->draw();
        }

        uint32_t GameStateManager::getActiveStateID() {
            return runningStateIDs_.empty() ? NO_STATE_ACTIVE : runningStateIDs_.front();
        }
    }
}
