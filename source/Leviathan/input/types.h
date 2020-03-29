/*! \file types.h
 *  \brief Definiert eingabespezifische Typen.
 *  \note Bestandteil der Leviathan Engine
 */

#ifndef LEVIATHAN_INPUT_TYPES_H
#define LEVIATHAN_INPUT_TYPES_H

#include <cstdint>

namespace leviathan {
    namespace input {

        /*! \brief Aktion, welche an Konsumenten versandt wird.
         */
        struct Action {
            uint32_t id;  //!< ID der Aktion (festgelegt in einer Mapping-Datei)
            bool isActive;  //!< ist die Aktion gerade aktiv?
        };
    }
}
#endif
