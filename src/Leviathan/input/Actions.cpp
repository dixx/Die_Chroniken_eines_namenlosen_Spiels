#include "Actions.h"
#include "ActionMapping.h"
#include "yaml-cpp/yaml.h"
#include <algorithm>

namespace leviathan {
    namespace input {
        Actions::Actions(IEventProducer& producer, core::Logger& logger) : _logger(logger), _producer(producer) {
            _producer.subscribe(*this, irr::EET_MOUSE_INPUT_EVENT);
            _producer.subscribe(*this, irr::EET_KEY_INPUT_EVENT);
            _producer.subscribe(*this, irr::EET_GUI_EVENT);
        }

        Actions::~Actions() {
            _producer.unsubscribe(*this, irr::EET_MOUSE_INPUT_EVENT);
            _producer.unsubscribe(*this, irr::EET_KEY_INPUT_EVENT);
            _producer.unsubscribe(*this, irr::EET_GUI_EVENT);
        }

        void Actions::subscribe(IActionConsumer& consumer, const uint32_t id) {
            auto found = std::find(_subscriptions[id].begin(), _subscriptions[id].end(), &consumer);
            if (found == _subscriptions[id].end()) {
                _subscriptions[id].push_back(&consumer);
            }
        }

        void Actions::unsubscribe(IActionConsumer& consumer, const uint32_t id) {
            auto found = std::find(_subscriptions[id].begin(), _subscriptions[id].end(), &consumer);
            if (found != _subscriptions[id].end()) {
                _subscriptions[id].erase(found);
            }
        }

        bool Actions::onEvent(const irr::SEvent& event) {
            if (converter(event.EventType) == nullptr) return false;

            std::vector<Action> actions = converter(event.EventType)->actionsFor(event);
            if (actions.empty()) return false;

            dispatchActions(actions);
            return true;
        }

        void Actions::loadFromFile(const irr::io::path& fileName) {
            _mouseConverter.clear();
            _keyboardConverter.clear();
            YAML::Node actionMap = YAML::LoadFile(fileName.c_str());
            for (const auto actionNode : actionMap) {
                ActionMapping action(actionNode);
                addMapping(action.id, action.primary);
                addMapping(action.id, action.secondary);
                _logger.text << "Actions - loaded actions: [" << action.id << "] = " << action.name << "("
                             << action.primary.code << ", " << action.secondary.code << ")";
                _logger.write(_logger.Level::DEBUG);
            }
        }

        void Actions::addMapping(const uint32_t actionId, const Input& input) {
            if (input.type == "mouse")
                _mouseConverter.addMapping(input.code, actionId);
            else if (input.type == "keyboard")
                _keyboardConverter.addMapping(input.code, actionId);
            else if (input.type == "gui")
                _guiConverter.addMapping(input.name, actionId);
        }

        void Actions::dispatchActions(const std::vector<Action>& actions) {
            for (auto action : actions) {
                if (_subscriptions[action.id].size() == 0) continue;

                // we iterate in reverse, because _subscriptions can shrink while being iterated
                for (uint32_t it = _subscriptions[action.id].size(); it != 0; it--) {
                    _subscriptions[action.id][it - 1]->onAction(action);
                }
            }
        }

        EventToActionConverter* Actions::converter(const uint32_t eventType) {
            switch (eventType) {
            case irr::EET_MOUSE_INPUT_EVENT:
                return &_mouseConverter;
            case irr::EET_KEY_INPUT_EVENT:
                return &_keyboardConverter;
            case irr::EET_GUI_EVENT:
                return &_guiConverter;
            default:
                return nullptr;
            }
        }
    }
}
