#include "Actions.h"
#include <iostream>

namespace leviathan {
    namespace input {
        Actions::Actions(IEventProducer& producer) {
            _actions[0];  // init default
            producer.subscribe(*this, irr::EET_MOUSE_INPUT_EVENT);
            producer.subscribe(*this, irr::EET_KEY_INPUT_EVENT);
        }

        void Actions::subscribe(IActionConsumer& consumer, const uint32_t id) {
            _subscriptions[id].insert(&consumer);
        }

        void Actions::unsubscribe(IActionConsumer& consumer, const uint32_t id) {
            _subscriptions[id].erase(&consumer);
        }

        bool Actions::onEvent(const irr::SEvent& event) {
            uint32_t id = 0;
            bool isActive = false;
            try {
                if (event.EventType == irr::EET_MOUSE_INPUT_EVENT) {
                    switch (event.MouseInput.Event) {
                    case irr::EMIE_LMOUSE_PRESSED_DOWN:
                        id = _converter[0].at(irr::EMBSM_LEFT);
                        isActive = true;
                        break;
                    case irr::EMIE_LMOUSE_LEFT_UP:
                        id = _converter[0].at(irr::EMBSM_LEFT);
                        break;
                    case irr::EMIE_RMOUSE_PRESSED_DOWN:
                        id = _converter[0].at(irr::EMBSM_RIGHT);
                        isActive = true;
                        break;
                    case irr::EMIE_RMOUSE_LEFT_UP:
                        id = _converter[0].at(irr::EMBSM_RIGHT);
                        break;
                    case irr::EMIE_MMOUSE_PRESSED_DOWN:
                        id = _converter[0].at(irr::EMBSM_MIDDLE);
                        isActive = true;
                        break;
                    case irr::EMIE_MMOUSE_LEFT_UP:
                        id = _converter[0].at(irr::EMBSM_MIDDLE);
                        break;
                    default:
                        return false;
                    }
                } else if (event.EventType == irr::EET_KEY_INPUT_EVENT) {
                    id = _converter[1].at(event.KeyInput.Key);
                    isActive = event.KeyInput.PressedDown;
                } else {
                    return false;
                }
            } catch (const std::out_of_range& e) {
                return false;
            }
            if (_subscriptions[id].empty()) {
                return false;
            }
            for (auto consumer : _subscriptions[id]) {
                consumer->onAction(id, isActive);
            }
            return true;
        }

        void Actions::loadFromFile(const irr::io::path& fileName) {
            YAML::Node actionMap = YAML::LoadFile(fileName.c_str());
            _actions.clear();
            _converter[0].clear();
            _converter[1].clear();
            for (const auto actionNode : actionMap) {
                Action action(actionNode);
                _actions[action.id] = action;
                addActionToConverter(action);
            }
        }

        // void Actions::mergeFromFile(const irr::io::path& fileName) {
        //     YAML::Node actionMap = YAML::LoadFile(fileName.c_str());
        //     for (const auto actionNode : actionMap) {
        //         Action action(actionNode);
        //         _actions[action.id] = action;
        //         addActionToConverter(action);
        //     }
        // }

        Actions::Input::Input(const YAML::Node& node)
        : name(node && node["name"] ? node["name"].as<std::string>() : "- None -"),
          type(node && node["type"] ? node["type"].as<std::string>() : "unknown"),
          id(node && node["id"] ? node["id"].as<uint32_t>() : 0),
          isActive(false),
          wasActive(false) {}

        Actions::Action::Action(const YAML::Node& node)
        : name(node && node["name"] ? node["name"].as<std::string>() : "nameless action"),
          description(node && node["description"] ? node["description"].as<std::string>() : ""),
          id(node && node["id"] ? node["id"].as<uint32_t>() : 0),
          internal(node && node["internal"]),
          primary(node["input_mappings"]["primary"]),
          secondary(node["input_mappings"]["secondary"]) {}

        void Actions::addActionToConverter(const Action& action) {
            if (action.primary.type == "mouse") {
                _converter[0][action.primary.id] = action.id;
            } else if (action.primary.type == "keyboard") {
                _converter[1][action.primary.id] = action.id;
            }
            if (action.secondary.type == "mouse") {
                _converter[0][action.secondary.id] = action.id;
            } else if (action.secondary.type == "keyboard") {
                _converter[1][action.secondary.id] = action.id;
            }
        }
    }
}
