/*! \file Input.h
 *  \brief Definition einer Eingabe.
 *  \note Bestandteil der Leviathan Engine
 *        Wird nur intern benutzt.
 */

#ifndef LEVIATHAN_INPUT_INPUT_H
#define LEVIATHAN_INPUT_INPUT_H

#include "yaml-cpp/yaml.h"
#include <cstdint>
#include <string>

namespace leviathan {
    namespace input {

        /*! \brief Definition einer Eingabe.
         */
        struct Input {
            Input() {/* ctor is needed for usage in std containers */};
            explicit Input(const YAML::Node& node);
            std::string name = "- None -";
            std::string type = "unknown";
            uint32_t code = 0;
            bool isActive = false;
            bool wasActive = false;
        };
    }
}
#endif
