#include "KeyboardEventActions.h"

namespace leviathan {
    namespace input {
        std::vector<Action> KeyboardEventActions::actionsFor(const irr::SEvent& event) {
            return createActions(event.KeyInput.Key, event.KeyInput.PressedDown);
        }

        void KeyboardEventActions::addMapping(const uint32_t inputId, const uint32_t actionId) {
            _actionsForInput[inputId].push_back(actionId);
            _actionsForInput[inputId].sort();
            _actionsForInput[inputId].unique();
        }
    }
}
