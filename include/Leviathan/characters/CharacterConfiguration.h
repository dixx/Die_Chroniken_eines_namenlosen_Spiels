/*! \file CharacterConfiguration.h
 *  \brief Konfiguration für einen NPC oder PC.
 *  \note Bestandteil der Leviathan Engine
 */

#ifndef LEVIATHAN_CHARACTERS_CHARACTER_CONFIGURATION_H
#define LEVIATHAN_CHARACTERS_CHARACTER_CONFIGURATION_H

#include <string>
#include <world/Node3DConfiguration.h>

namespace leviathan {
    namespace characters {
        /*! \brief Konfiguration für einen NPC oder PC.
         */
        struct CharacterConfiguration {
            std::string name = "";
            std::string internalName = "";
            world::Node3DConfiguration playableFigurineConfiguration = {};
        };
    }
}
#endif
