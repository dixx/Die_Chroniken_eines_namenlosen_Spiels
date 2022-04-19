/*! \file MouseEventActions.h
 *  \brief Bietet Mappings von Maus-Eingaben zu in-Game Aktionen.
 *  \note Bestandteil der Leviathan Engine
 *        Wird nur intern benutzt.
 */

#ifndef LEVIATHAN_INPUT_MOUSE_EVENT_ACTIONS_CONVERTER_H
#define LEVIATHAN_INPUT_MOUSE_EVENT_ACTIONS_CONVERTER_H

#include "EventToActionConverter.h"
#include <cstdint>
#include <vector>

namespace irr {
    struct SEvent;
}

namespace leviathan {
    namespace input {
        struct Action;

        class MouseEventActions final : public EventToActionConverter {
        public:
            MouseEventActions() = default;
            ~MouseEventActions() = default;
            MouseEventActions(const MouseEventActions&) = delete;
            MouseEventActions(MouseEventActions&&) = default;
            MouseEventActions& operator=(const MouseEventActions&) = delete;
            MouseEventActions& operator=(const MouseEventActions&&) = delete;

            std::vector<Action> actionsFor(const irr::SEvent& event) override;
            void addMapping(const uint32_t buttonCode, const uint32_t actionId);

        private:
            bool isLeftButton(const irr::SEvent& event) const;
            bool isMiddleButton(const irr::SEvent& event) const;
            bool isRightButton(const irr::SEvent& event) const;
        };
    }
}
#endif
