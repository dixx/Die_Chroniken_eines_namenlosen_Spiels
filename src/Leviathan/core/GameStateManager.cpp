#include "GameStateManager.h"
#include <stdexcept>

namespace leviathan {
    namespace core {
        GameStateManager::GameStateManager(Logger& logger) : logger_(logger) {}

        void GameStateManager::add(IGameState& gameState, const uint32_t id) {
            if (id == NO_STATE_ACTIVE) throw std::invalid_argument("0xffffffff is not allowed as an ID here, sorry!");
            if (states_.find(id) == states_.end()) {
                states_[id] = &gameState;
                logger_.text << "GameStateManager - add state: " << id << " = " << &gameState;
                logger_.write(Logger::Level::ALL);
            } else {
                logger_.text << "[Warning] - GameStateManager - cannot add state " << id << ", already exists!";
                logger_.write(Logger::Level::DEBUG);
            }
        }

        void GameStateManager::transitTo(const uint32_t id) {
            if (isUnknownState(id) || isAlreadyActive(id) || isDeeperDownTheStack(id)) {
                logger_.text << "GameStateManager - transit to " << id << " failed.";
                logger_.write(Logger::Level::ALL);
                return;
            }
            if (getActiveStateID() != NO_STATE_ACTIVE) states_[getActiveStateID()]->setInactive();
            if (isSecondOnStack(id)) {
                runningStateIDs_.pop_front();
                logger_.text << "GameStateManager - transit to " << id << " by pop.";
                logger_.write(Logger::Level::ALL);
            } else {
                runningStateIDs_.push_front(id);
                logger_.text << "GameStateManager - transit to " << id << " by push.";
                logger_.write(Logger::Level::ALL);
            }
            states_[id]->setActive();
        }

        void GameStateManager::update(const float elapsedSeconds) {
            uint32_t id = getActiveStateID();
            if (id == NO_STATE_ACTIVE) return;
            states_[id]->update(elapsedSeconds);
        }

        void GameStateManager::draw() {
            uint32_t id = getActiveStateID();
            if (id == NO_STATE_ACTIVE) return;
            states_[id]->draw();
        }

        uint32_t GameStateManager::getActiveStateID() const {
            return runningStateIDs_.empty() ? NO_STATE_ACTIVE : runningStateIDs_.front();
        }

        /* private */

        bool GameStateManager::isUnknownState(const uint32_t id) const {
            if (states_.find(id) == states_.end()) {
                logger_.text << "[Warning] - GameStateManager - unknown state " << id << " requested!";
                logger_.write(Logger::Level::DEBUG);
                return true;
            }
            return false;
        }

        bool GameStateManager::isAlreadyActive(const uint32_t id) const {
            if (getActiveStateID() == id) {
                logger_.text << "[Warning] - GameStateManager - active state " << id << " requested!";
                logger_.write(Logger::Level::DEBUG);
                return true;
            }
            return false;
        }

        bool GameStateManager::isSecondOnStack(const uint32_t id) const {
            return runningStateIDs_.size() > 1 && *std::next(runningStateIDs_.begin()) == id;
        }

        bool GameStateManager::isDeeperDownTheStack(const uint32_t id) const {
            if (runningStateIDs_.size() < 2 || isSecondOnStack(id)) return false;
            if (isInStack(id)) {
                logger_.text << "[Warning] - GameStateManager - requested state " << id
                             << " is too deep down the stack!";
                logger_.write(Logger::Level::DEBUG);
                return true;
            }
            return false;
        }

        bool GameStateManager::isInStack(const uint32_t id) const {
            for (auto& item : runningStateIDs_) {
                if (item == id) return true;
            }
            return false;
        }
    }
}