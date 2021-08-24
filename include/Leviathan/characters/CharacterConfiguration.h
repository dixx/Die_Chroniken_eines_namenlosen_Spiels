/*! \file CharacterConfiguration.h
 *  \brief Konfiguration für einen NPC oder PC.
 *  \note Bestandteil der Leviathan Engine
 */

#ifndef LEVIATHAN_PUBLIC_INTERFACES_CHARACTERS_CHARACTERCONFIGURATION_H
#define LEVIATHAN_PUBLIC_INTERFACES_CHARACTERS_CHARACTERCONFIGURATION_H

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
