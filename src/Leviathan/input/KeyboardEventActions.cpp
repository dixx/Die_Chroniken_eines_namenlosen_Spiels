#include "KeyboardEventActions.h"
#include "IEventReceiver.h"
#include <input/Action.h>

namespace leviathan {
    namespace input {
        std::vector<Action> KeyboardEventActions::actionsFor(const irr::SEvent& event) {
            return createActions(event.KeyInput.Key, event.KeyInput.PressedDown);
        }

        void KeyboardEventActions::addMapping(const uint32_t keyCode, const uint32_t actionId) {
            _actionsForInput[keyCode].push_back(actionId);
            _actionsForInput[keyCode].sort();
            _actionsForInput[keyCode].unique();
        }
    }
}
