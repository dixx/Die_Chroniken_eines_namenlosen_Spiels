#include "Actions.h"
#include "types.h"
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
            std::vector<Action> actions;
            if (event.EventType == irr::EET_MOUSE_INPUT_EVENT) {
                actions = _mouseConverter.actionsFor(event);
            } else if (event.EventType == irr::EET_KEY_INPUT_EVENT) {
                actions = _keyboardConverter.actionsFor(event);
            } else if (event.EventType == irr::EET_GUI_EVENT) {
            } else {
                return false;
            }
            if (actions.empty()) {
                return false;
            }
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

        Actions::Input::Input(const YAML::Node& node)
        : name(node && node["name"] ? node["name"].as<std::string>() : "- None -"),
          type(node && node["type"] ? node["type"].as<std::string>() : "unknown"),
          id(node && node["id"] ? node["id"].as<uint32_t>() : 0), isActive(false), wasActive(false) {}

        Actions::ActionMapping::ActionMapping(const YAML::Node& node)
        : name(node && node["name"] ? node["name"].as<std::string>() : "nameless action"),
          description(node && node["description"] ? node["description"].as<std::string>() : ""),
          id(node && node["id"] ? node["id"].as<uint32_t>() : 0), internal(node && node["internal"]),
          primary(node["input_mappings"]["primary"]), secondary(node["input_mappings"]["secondary"]) {}

        void Actions::addActionToConverter(const ActionMapping& action) {
            if (action.primary.type == "mouse") {
                _mouseConverter.addMapping(action.primary.id, action.id);
            } else if (action.primary.type == "keyboard") {
                _keyboardConverter.addMapping(action.primary.id, action.id);
            } else if (action.primary.type == "gui") {
            }
            if (action.secondary.type == "mouse") {
                _mouseConverter.addMapping(action.secondary.id, action.id);
            } else if (action.secondary.type == "keyboard") {
                _keyboardConverter.addMapping(action.secondary.id, action.id);
            } else if (action.secondary.type == "gui") {
            }
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
    }
}
