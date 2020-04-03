#include "Actions.h"
#include "yaml-cpp/yaml.h"
#include <algorithm>

namespace leviathan {
    namespace input {
        Actions::Actions(IEventProducer& producer, core::Logger& logger) : _logger(logger), _producer(producer) {
            _actions[0];  // init default
            _producer.subscribe(*this, irr::EET_MOUSE_INPUT_EVENT);
            _producer.subscribe(*this, irr::EET_KEY_INPUT_EVENT);
        }

        Actions::~Actions() {
            _producer.unsubscribe(*this, irr::EET_MOUSE_INPUT_EVENT);
            _producer.unsubscribe(*this, irr::EET_KEY_INPUT_EVENT);
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
            YAML::Node actionMap = YAML::LoadFile(fileName.c_str());
            _actions.clear();
            _mouseConverter.clear();
            _keyboardConverter.clear();
            for (const auto actionNode : actionMap) {
                ActionMapping action(actionNode);
                _actions[action.id] = action;
                addActionToConverter(action);
            }
            for (const auto& p : _actions) {
                _logger.text << "Actions - loaded actions: [" << p.first << "] = " << p.second.name << "("
                             << p.second.primary.id << ", " << p.second.secondary.id << ")";
                _logger.write(_logger.Level::DEBUG);
            }
        }

        void Actions::addActionToConverter(const ActionMapping& mapping) {
            if (converter(mapping.primary.type))
                converter(mapping.primary.type)->addMapping(mapping.primary.id, mapping.id);
            if (converter(mapping.secondary.type))
                converter(mapping.secondary.type)->addMapping(mapping.secondary.id, mapping.id);
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
            default:
                return nullptr;
            }
        }

        EventToActionConverter* Actions::converter(const std::string& inputType) {
            if (inputType == "mouse")
                return &_mouseConverter;
            else if (inputType == "keyboard")
                return &_keyboardConverter;
            else
                return nullptr;
        }
    }
}
