/*! \file KeyboardEventActions.h
 *  \brief Bietet Mappings von Keyboard-Eingaben zu in-Game Aktionen.
 *  \note Bestandteil der Leviathan Engine
 *        Wird nur intern benutzt.
 */

#ifndef LEVIATHAN_INPUT_KEYBOARD_EVENT_ACTIONS_CONVERTER_H
#define LEVIATHAN_INPUT_KEYBOARD_EVENT_ACTIONS_CONVERTER_H

#include "EventToActionConverter.h"
#include <cstdint>
#include <vector>

namespace irr {
    struct SEvent;
}

namespace leviathan {
    namespace input {
        struct Action;

        class KeyboardEventActions final : public EventToActionConverter {
        public:
            KeyboardEventActions() = default;
            ~KeyboardEventActions() = default;
            KeyboardEventActions(const KeyboardEventActions&) = delete;
            KeyboardEventActions(KeyboardEventActions&&) = default;
            KeyboardEventActions& operator=(const KeyboardEventActions&) = delete;
            KeyboardEventActions& operator=(const KeyboardEventActions&&) = delete;

            std::vector<Action> actionsFor(const irr::SEvent& event) override;
            void addMapping(const uint32_t keyCode, const uint32_t actionId);
        };
    }
}
#endif
