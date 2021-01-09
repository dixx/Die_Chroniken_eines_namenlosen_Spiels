#include "ActionMapping.h"

namespace leviathan {
    namespace input {
        ActionMapping::ActionMapping(const YAML::Node& node)
        : name(node ? node["name"].as<std::string>("nameless action") : "nameless action"),
          description(node ? node["description"].as<std::string>("") : ""), id(node ? node["id"].as<uint32_t>(0) : 0),
          internal(node && node["internal"]), primary(node["input_mappings"]["primary"]),
          secondary(node["input_mappings"]["secondary"]) {}
    }
}
