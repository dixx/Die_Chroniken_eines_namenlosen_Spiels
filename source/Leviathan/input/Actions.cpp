#include "Actions.h"
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
            std::list<uint32_t> action_ids = {};
            bool isActive = false;
            try {
                if (event.EventType == irr::EET_MOUSE_INPUT_EVENT) {
                    auto mouseEvent = event.MouseInput.Event;
                    switch (mouseEvent) {
                    case irr::EMIE_LMOUSE_PRESSED_DOWN:
                    case irr::EMIE_LMOUSE_LEFT_UP:
                        action_ids = _converter[MOUSE].at(irr::EMBSM_LEFT);
                        break;
                    case irr::EMIE_RMOUSE_PRESSED_DOWN:
                    case irr::EMIE_RMOUSE_LEFT_UP:
                        action_ids = _converter[MOUSE].at(irr::EMBSM_RIGHT);
                        break;
                    case irr::EMIE_MMOUSE_PRESSED_DOWN:
                    case irr::EMIE_MMOUSE_LEFT_UP:
                        action_ids = _converter[MOUSE].at(irr::EMBSM_MIDDLE);
                        break;
                    default:
                        return false;
                    }
                    isActive = (mouseEvent == irr::EMIE_LMOUSE_PRESSED_DOWN
                                || mouseEvent == irr::EMIE_RMOUSE_PRESSED_DOWN
                                || mouseEvent == irr::EMIE_MMOUSE_PRESSED_DOWN);
                } else if (event.EventType == irr::EET_KEY_INPUT_EVENT) {
                    action_ids = _converter[KEYBOARD].at(event.KeyInput.Key);
                    isActive = event.KeyInput.PressedDown;
                } else {
                    return false;
                }
            } catch (const std::out_of_range& e) {
                return false;
            }
            if (action_ids.empty()) {
                return false;
            }
            dispatchAction(action_ids, isActive);
            return true;
        }

        void Actions::loadFromFile(const irr::io::path& fileName) {
            YAML::Node actionMap = YAML::LoadFile(fileName.c_str());
            _actions.clear();
            _converter[MOUSE].clear();
            _converter[KEYBOARD].clear();
            for (const auto actionNode : actionMap) {
                Action action(actionNode);
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

        Actions::Action::Action(const YAML::Node& node)
        : name(node && node["name"] ? node["name"].as<std::string>() : "nameless action"),
          description(node && node["description"] ? node["description"].as<std::string>() : ""),
          id(node && node["id"] ? node["id"].as<uint32_t>() : 0), internal(node && node["internal"]),
          primary(node["input_mappings"]["primary"]), secondary(node["input_mappings"]["secondary"]) {}

        void Actions::addActionToConverter(const Action& action) {
            if (action.primary.type == "mouse") {
                _converter[MOUSE][action.primary.id].push_back(action.id);
                _converter[MOUSE][action.primary.id].unique();
            } else if (action.primary.type == "keyboard") {
                _converter[KEYBOARD][action.primary.id].push_back(action.id);
                _converter[KEYBOARD][action.primary.id].unique();
            }
            if (action.secondary.type == "mouse") {
                _converter[MOUSE][action.secondary.id].push_back(action.id);
                _converter[MOUSE][action.secondary.id].unique();
            } else if (action.secondary.type == "keyboard") {
                _converter[KEYBOARD][action.secondary.id].push_back(action.id);
                _converter[KEYBOARD][action.secondary.id].unique();
            }
        }

        void Actions::dispatchAction(const std::list<uint32_t>& action_ids, bool isActive) {
            for (auto id : action_ids) {
                if (_subscriptions[id].size() == 0) continue;
                // we iterate in reverse, because _subscriptions can shrink while being iterated
                for (uint32_t it = _subscriptions[id].size(); it != 0; it--) {
                    _subscriptions[id][it - 1]->onAction(id, isActive);
                }
            }
        }
    }
}
