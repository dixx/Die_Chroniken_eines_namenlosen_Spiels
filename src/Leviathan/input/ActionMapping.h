/*! \file ActionMapping.h
 *  \brief Zuordnung von Aktion zu Eingaben.
 *  \note Bestandteil der Leviathan Engine
 *        Wird nur intern benutzt.
 */

#ifndef LEVIATHAN_ACTION_MAPPING_H
#define LEVIATHAN_ACTION_MAPPING_H

#include "Input.h"
#include "yaml-cpp/yaml.h"
#include <cstdint>
#include <string>

namespace leviathan {
    namespace input {

        /*! \brief Zuordnung von Aktion zu Eingaben.
         */
        struct ActionMapping {
            ActionMapping() {/* ctor is needed for usage in std containers */};
            explicit ActionMapping(const YAML::Node& node);
            std::string name = "nameless action";
            std::string description = "";
            uint32_t id = 0;
            bool internal = false;
            Input primary = Input();
            Input secondary = Input();
        };
    }
}
#endif
