/*! \file EventToActionConverter.h
 *  \brief Bietet Mappings von beliebigen Eingaben zu in-Game Aktionen.
 *  \note Bestandteil der Leviathan Engine
 *        Wird nur intern benutzt.
 */

#ifndef LEVIATHAN_INPUT_EVENT_TO_ACTION_CONVERTER_H
#define LEVIATHAN_INPUT_EVENT_TO_ACTION_CONVERTER_H

#include "irrlicht.h"
#include "types.h"
#include <list>
#include <map>

namespace leviathan {
    namespace input {
        class EventToActionConverter {
        public:
            virtual ~EventToActionConverter() {}

            void clear();
            void addMapping(const uint32_t inputId, const uint32_t actionId);
            virtual const std::list<Action>& actionsFor(const irr::SEvent& event) = 0;

        protected:
            std::map<uint32_t, std::list<Action>> _actionsForInput = std::map<uint32_t, std::list<Action>>();
        }
    }
}
#endif
