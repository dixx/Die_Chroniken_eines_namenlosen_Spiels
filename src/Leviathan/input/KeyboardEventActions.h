/*! \file KeyboardEventActions.h
 *  \brief Bietet Mappings von Keyboard-Eingaben zu in-Game Aktionen.
 *  \note Bestandteil der Leviathan Engine
 *        Wird nur intern benutzt.
 */

#ifndef LEVIATHAN_INPUT_KEYBOARD_EVENT_ACTIONS_CONVERTER_H
#define LEVIATHAN_INPUT_KEYBOARD_EVENT_ACTIONS_CONVERTER_H

#include "Action.h"
#include "EventToActionConverter.h"
#include "irrlicht.h"
#include <cstdint>
#include <vector>

namespace leviathan {
    namespace input {
        class KeyboardEventActions : public EventToActionConverter {
        public:
            std::vector<Action> actionsFor(const irr::SEvent& event);
            void addMapping(const uint32_t keyCode, const uint32_t actionId);
        };
    }
}
#endif
