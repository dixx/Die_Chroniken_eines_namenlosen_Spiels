/*! \file EventToActionConverter.h
 *  \brief Bietet Mappings von beliebigen Eingaben zu in-Game Aktionen.
 *  \note Bestandteil der Leviathan Engine
 *        Wird nur intern benutzt.
 */

#ifndef LEVIATHAN_INPUT_EVENT_TO_ACTION_CONVERTER_H
#define LEVIATHAN_INPUT_EVENT_TO_ACTION_CONVERTER_H

#include <cstdint>
#include <list>
#include <map>
#include <vector>

namespace irr {
    struct SEvent;
}

namespace leviathan {
    namespace input {
        struct Action;

        class EventToActionConverter {
        public:
            virtual ~EventToActionConverter() {}

            void clear();
            virtual std::vector<Action> actionsFor(const irr::SEvent& event) = 0;

        protected:
            std::map<uint32_t, std::list<uint32_t>> _actionsForInput = std::map<uint32_t, std::list<uint32_t>>();
            std::list<uint32_t> _emptyList = std::list<uint32_t>();

            std::vector<Action> createActions(const uint32_t inputId, const bool isActive);
            std::list<uint32_t>& actionIdsFor(const uint32_t inputId);
        };
    }
}
#endif
