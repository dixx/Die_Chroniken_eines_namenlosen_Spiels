#include "Input.h"

namespace leviathan {
    namespace input {
        Input::Input(const YAML::Node& node)
        : name(node && node["name"] ? node["name"].as<std::string>() : "- None -"),
          type(node && node["type"] ? node["type"].as<std::string>() : "unknown"),
          id(node && node["id"] ? node["id"].as<uint32_t>() : 0), isActive(false), wasActive(false) {}
    }
}
