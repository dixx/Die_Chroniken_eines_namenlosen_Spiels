/*! \file EventToActionConverter.h
 *  \brief Bietet Mappings von Maus-Eingaben zu in-Game Aktionen.
 *  \note Bestandteil der Leviathan Engine
 *        Wird nur intern benutzt.
 */

#ifndef LEVIATHAN_INPUT_MOUSE_EVENT_ACTIONS_CONVERTER_H
#define LEVIATHAN_INPUT_MOUSE_EVENT_ACTIONS_CONVERTER_H

#include "EventToActionConverter.h"

namespace leviathan {
    namespace input {
        class MouseEventActions : public EventToActionConverter {
        public:
            std::vector<Action> actionsFor(const irr::SEvent& event);
        };
    }
}
#endif
