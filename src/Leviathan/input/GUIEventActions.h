/*! \file GUIEventActions.h
 *  \brief Bietet Mappings von GUI-Element-Änderungen zu in-Game Aktionen.
 *  \note Bestandteil der Leviathan Engine
 *        Wird nur intern benutzt.
 */

#ifndef LEVIATHAN_INPUT_GUI_EVENT_ACTIONS_CONVERTER_H
#define LEVIATHAN_INPUT_GUI_EVENT_ACTIONS_CONVERTER_H

#include "EventToActionConverter.h"
#include <cstdint>
#include <list>
#include <map>
#include <string>
#include <vector>

namespace irr {
    struct SEvent;
}

namespace leviathan {
    namespace input {
        struct Action;

        class GUIEventActions final : public EventToActionConverter {
        public:
            std::vector<Action> actionsFor(const irr::SEvent& event);
            void addMapping(const std::string inputName, const uint32_t actionId);

        private:
            std::map<std::string, std::list<uint32_t>> _actionsForInput = std::map<std::string, std::list<uint32_t>>();

            std::vector<Action> createActions(const std::string& inputName, const bool isActive);
            std::list<uint32_t>& actionIdsFor(const std::string& inputName);
        };
    }
}
#endif
