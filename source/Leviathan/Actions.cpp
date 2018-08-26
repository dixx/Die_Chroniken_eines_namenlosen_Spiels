#include "Actions.h"

namespace leviathan
{
    namespace input
    {
        Actions::Actions()
        : _custom(),
          _internal()
        {
            _custom[0]; // init default
        }

        bool Actions::inProgress(const uint32_t id) const {
            return getAction(id).primary.isActive || getAction(id).secondary.isActive;
        }

        bool Actions::inactive(const uint32_t id) const {
            return !inProgress(id);
        }

        bool Actions::justStarted(const uint32_t id) const {
            return (getAction(id).primary.isActive && !getAction(id).primary.wasActive)
                || (getAction(id).secondary.isActive && !getAction(id).secondary.wasActive);
        }

        bool Actions::justStopped(const uint32_t id) const {
            return (!getAction(id).primary.isActive && getAction(id).primary.wasActive)
                || (!getAction(id).secondary.isActive && getAction(id).secondary.wasActive);
        }

        void Actions::mergeFromFile(const irr::io::path& fileName) {
            YAML::Node actionMap = YAML::LoadFile(fileName.c_str());
            const YAML::Node& customActions = actionMap["customizable"];
            const YAML::Node& internalActions = actionMap["internal"];
            if (customActions) {
                for (const auto actionNode : customActions) {
                    Action action(actionNode);
                    _custom[action.id] = action;
                }
            }
            if (internalActions) {
                for (const auto actionNode : internalActions) {
                    Action action(actionNode);
                    _internal[action.id] = action;
                }
            }
        }

        Actions::Input::Input(const YAML::Node& node)
        : name(node && node["name"] ? node["name"].as<std::string>() : "- None -"),
          type(node && node["type"] ? node["type"].as<std::string>() : "unknown"),
          id(node && node["id"] ? node["id"].as<uint32_t>() : 0),
          isActive(false),
          wasActive(false)
        {
            // nop
        }

        Actions::Input::Input()
        : name("- None -"),
          type("unknown"),
          id(0),
          isActive(false),
          wasActive(false)
        {
            // std::map needs this
        }

        Actions::Action::Action(const YAML::Node& node)
        : name(node && node["name"] ? node["name"].as<std::string>() : "nameless action"),
          description(node && node["description"] ? node["description"].as<std::string>() : ""),
          id(node && node["id"] ? node["id"].as<uint32_t>() : 0),
          primary(node["input_mappings"]["primary"]),
          secondary(node["input_mappings"]["secondary"])
        {
            // nop
        }

        Actions::Action::Action()
        : name("nameless action"),
          description(""),
          id(0),
          primary(),
          secondary()
        {
            // std::map needs this
        }

        const Actions::Action& Actions::getAction(const uint32_t id) const {
            try {
                return _custom.at(id);
            } catch(const std::out_of_range& e) {
                return _custom.at(0);
            }
        }
    }
}
