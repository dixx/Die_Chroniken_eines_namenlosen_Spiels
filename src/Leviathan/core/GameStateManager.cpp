#include "GameStateManager.h"
#include "Logger.h"
#include <stdexcept>

namespace leviathan {
    namespace core {
        GameStateManager::GameStateManager(Logger& logger) : mLogger(logger) {}

        void GameStateManager::add(IGameState& gameState, const uint32_t id) {
            if (id == NO_STATE_ACTIVE) throw std::invalid_argument("0xffffffff is not allowed as an ID here, sorry!");
            if (mStates.find(id) == mStates.end()) {
                mStates[id] = &gameState;
                mLogger.text << "GameStateManager - add state: " << id << " = " << &gameState;
                mLogger.write(Logger::Level::ALL);
            } else {
                mLogger.text << "[Warning] - GameStateManager - cannot add state " << id << ", already exists!";
                mLogger.write(Logger::Level::DEBUG);
            }
        }

        void GameStateManager::transitTo(const uint32_t id) {
            if (isUnknownState(id) || isAlreadyActive(id) || isDeeperDownTheStack(id)) {
                mLogger.text << "GameStateManager - transit to " << id << " failed.";
                mLogger.write(Logger::Level::ALL);
                return;
            }
            if (getActiveStateID() != NO_STATE_ACTIVE) mStates[getActiveStateID()]->setInactive();
            if (isSecondOnStack(id)) {
                mRunningStateIDs.pop_front();
                mLogger.text << "GameStateManager - transit to " << id << " by pop.";
                mLogger.write(Logger::Level::ALL);
            } else {
                mRunningStateIDs.push_front(id);
                mLogger.text << "GameStateManager - transit to " << id << " by push.";
                mLogger.write(Logger::Level::ALL);
            }
            mStates[id]->setActive();
        }

        void GameStateManager::update(const float elapsedSeconds) {
            uint32_t id = getActiveStateID();
            if (id == NO_STATE_ACTIVE) return;
            mStates[id]->update(elapsedSeconds);
        }

        void GameStateManager::draw() {
            uint32_t id = getActiveStateID();
            if (id == NO_STATE_ACTIVE) return;
            mStates[id]->draw();
        }

        uint32_t GameStateManager::getActiveStateID() const {
            return mRunningStateIDs.empty() ? NO_STATE_ACTIVE : mRunningStateIDs.front();
        }

        /* private */

        bool GameStateManager::isUnknownState(const uint32_t id) const {
            if (mStates.find(id) == mStates.end()) {
                mLogger.text << "[Warning] - GameStateManager - unknown state " << id << " requested!";
                mLogger.write(Logger::Level::DEBUG);
                return true;
            }
            return false;
        }

        bool GameStateManager::isAlreadyActive(const uint32_t id) const {
            if (getActiveStateID() == id) {
                mLogger.text << "[Warning] - GameStateManager - active state " << id << " requested!";
                mLogger.write(Logger::Level::DEBUG);
                return true;
            }
            return false;
        }

        bool GameStateManager::isSecondOnStack(const uint32_t id) const {
            return mRunningStateIDs.size() > 1 && *std::next(mRunningStateIDs.begin()) == id;
        }

        bool GameStateManager::isDeeperDownTheStack(const uint32_t id) const {
            if (mRunningStateIDs.size() < 2 || isSecondOnStack(id)) return false;
            if (isInStack(id)) {
                mLogger.text << "[Warning] - GameStateManager - requested state " << id
                             << " is too deep down the stack!";
                mLogger.write(Logger::Level::DEBUG);
                return true;
            }
            return false;
        }

        bool GameStateManager::isInStack(const uint32_t id) const {
            for (auto& item : mRunningStateIDs) {
                if (item == id) return true;
            }
            return false;
        }
    }
}
