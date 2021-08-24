#include "EventToActionConverter.h"
#include <input/Action.h>

namespace leviathan {
    namespace input {
        void EventToActionConverter::clear() {
            _actionsForInput.clear();
        }

        std::list<uint32_t>& EventToActionConverter::actionIdsFor(const uint32_t inputId) {
            try {
                return _actionsForInput.at(inputId);
            } catch (const std::out_of_range& e) {
                return _emptyList;
            }
        }

        std::vector<Action> EventToActionConverter::createActions(const uint32_t inputId, const bool isActive) {
            std::vector<Action> result;
            for (uint32_t actionId : actionIdsFor(inputId)) {
                result.push_back({actionId, isActive});
            }
            return result;
        }
    }
}
