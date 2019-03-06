#include "GameStateManager.h"
#include <iterator>
#include <stdexcept>

namespace leviathan {
    namespace core {
        void GameStateManager::add(IGameState& gameState, uint32_t id) {
            if (id == NO_STATE_ACTIVE)
                throw std::invalid_argument("0xffffffff is not allowed as an ID here, sorry!");
            if (isUnknownState(id)) {
                states_[id] = &gameState;
            } else {
                // TODO: log it!
            }
        }

        void GameStateManager::transitTo(uint32_t id) {
            if (isUnknownState(id)) {
                // TODO: invalid request, log it!
            } else if (runningStateIDs_.empty()) {
                runningStateIDs_.push_front(id);
            } else if (runningStateIDs_.front() == id) {
                // TODO: bad request, log it!
            } else if (isSecondOnStack(id)) {
                runningStateIDs_.pop_front();
            } else if (isInStack(id)) {
                // TODO: bad request, log it!
            } else {
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

        bool GameStateManager::isUnknownState(const uint32_t id) const {
            return states_.find(id) == states_.end();
        }

        bool GameStateManager::isSecondOnStack(const uint32_t id) const {
            return runningStateIDs_.size() > 1 && *std::next(runningStateIDs_.begin()) == id;
        }

        bool GameStateManager::isInStack(const uint32_t id) const {
            for (auto& item : runningStateIDs_) {
                if (item == id)
                    return true;
            }
            return false;
        }
    }
}
