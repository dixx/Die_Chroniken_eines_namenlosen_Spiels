/*! \file Action.h
 *  \brief Aktion, welche von registrierten Konsumenten empfangen werden kann.
 *  \note Bestandteil der Leviathan Engine
 */

#ifndef LEVIATHAN_INPUT_ACTION_H
#define LEVIATHAN_INPUT_ACTION_H

#include <cstdint>

namespace leviathan {
    namespace input {

        /*! \brief Aktion, welche von registrierten Konsumenten empfangen werden kann.
         */
        struct Action {
            uint32_t id;  //!< ID der Aktion (festgelegt in einer Mapping-Datei)
            bool isActive;  //!< ist die Aktion gerade aktiv?
        };
    }
}
#endif
