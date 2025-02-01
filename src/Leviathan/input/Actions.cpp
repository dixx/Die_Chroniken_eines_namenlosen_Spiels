#include "Actions.h"
#include "ActionMapping.h"
#include "IEventProducer.h"
#include "IEventReceiver.h"
#include "Input.h"
#include "yaml-cpp/yaml.h"
#include <algorithm>
#include <core/ILogger.h>
#include <input/Action.h>

namespace leviathan {
    namespace input {
        Actions::Actions(IEventProducer& producer, core::ILogger& logger) : mLogger(logger), mProducer(producer) {
            mProducer.subscribe(*this, irr::EET_MOUSE_INPUT_EVENT);
            mProducer.subscribe(*this, irr::EET_KEY_INPUT_EVENT);
            mProducer.subscribe(*this, irr::EET_GUI_EVENT);
        }

        Actions::~Actions() {
            mProducer.unsubscribe(*this, irr::EET_MOUSE_INPUT_EVENT);
            mProducer.unsubscribe(*this, irr::EET_KEY_INPUT_EVENT);
            mProducer.unsubscribe(*this, irr::EET_GUI_EVENT);
        }

        void Actions::subscribe(IActionConsumer& consumer, const uint32_t id) {
            auto found = std::find(mSubscriptions[id].begin(), mSubscriptions[id].end(), &consumer);
            if (found == mSubscriptions[id].end()) {
                mSubscriptions[id].push_back(&consumer);
            }
        }

        void Actions::unsubscribe(IActionConsumer& consumer, const uint32_t id) {
            auto found = std::find(mSubscriptions[id].begin(), mSubscriptions[id].end(), &consumer);
            if (found != mSubscriptions[id].end()) {
                mSubscriptions[id].erase(found);
            }
        }

        bool Actions::onEvent(const irr::SEvent& event) {
            if (converter(event.EventType) == nullptr) return false;

            std::vector<Action> actions = converter(event.EventType)->actionsFor(event);
            if (actions.empty()) return false;

            dispatchActions(actions);
            return true;
        }

        void Actions::loadFromFile(const char* fileName) {
            mMouseConverter.clear();
            mKeyboardConverter.clear();
            YAML::Node actionMap = YAML::LoadFile(fileName);
            for (const auto actionNode : actionMap) {
                ActionMapping action(actionNode);
                addMapping(action.id, action.primary);
                addMapping(action.id, action.secondary);
                mLogger.text << "Actions - loaded actions: [" << action.id << "] = " << action.name << "("
                             << action.primary.code << ", " << action.secondary.code << ")";
                mLogger.write(mLogger.Level::DEBUG);
            }
        }

        void Actions::addMapping(const uint32_t actionId, const Input& input) {
            if (input.type == "mouse")
                mMouseConverter.addMapping(input.code, actionId);
            else if (input.type == "keyboard")
                mKeyboardConverter.addMapping(input.code, actionId);
            else if (input.type == "gui")
                mGuiConverter.addMapping(input.name, actionId);
        }

        void Actions::dispatchActions(const std::vector<Action>& actions) {
            for (auto action : actions) {
                if (mSubscriptions[action.id].size() == 0) continue;

                // we iterate in reverse, because mSubscriptions can shrink while being iterated
                for (auto it = mSubscriptions[action.id].size(); it != 0; it--) {
                    mSubscriptions[action.id][it - 1]->onAction(action);
                }
            }
        }

        EventToActionConverter* Actions::converter(const uint32_t eventType) {
            switch (eventType) {
            case irr::EET_MOUSE_INPUT_EVENT:
                return &mMouseConverter;
            case irr::EET_KEY_INPUT_EVENT:
                return &mKeyboardConverter;
            case irr::EET_GUI_EVENT:
                return &mGuiConverter;
            default:
                return nullptr;
            }
        }
    }
}
