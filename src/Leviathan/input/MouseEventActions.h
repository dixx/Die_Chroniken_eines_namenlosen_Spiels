/*! \file MouseEventActions.h
 *  \brief Bietet Mappings von Maus-Eingaben zu in-Game Aktionen.
 *  \note Bestandteil der Leviathan Engine
 *        Wird nur intern benutzt.
 */

#ifndef LEVIATHAN_INPUT_MOUSE_EVENT_ACTIONS_CONVERTER_H
#define LEVIATHAN_INPUT_MOUSE_EVENT_ACTIONS_CONVERTER_H

#include "EventToActionConverter.h"
#include "irrlicht.h"
#include <cstdint>
#include <vector>

namespace leviathan {
    namespace input {
        struct Action;

        class MouseEventActions final : public EventToActionConverter {
        public:
            std::vector<Action> actionsFor(const irr::SEvent& event);
            void addMapping(const uint32_t buttonCode, const uint32_t actionId);

        private:
            bool isLeftButton(const irr::SEvent& event) const;
            bool isMiddleButton(const irr::SEvent& event) const;
            bool isRightButton(const irr::SEvent& event) const;
        };
    }
}
#endif
