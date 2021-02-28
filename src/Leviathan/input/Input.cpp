#include "Input.h"

namespace leviathan {
    namespace input {
        Input::Input(const YAML::Node& node)
        : name(node ? node["name"].as<std::string>("- None -") : "- None -"),
          type(node ? node["type"].as<std::string>("unknown") : "unknown"), id(node ? node["id"].as<uint32_t>(0) : 0),
          isActive(false), wasActive(false) {}
    }
}
