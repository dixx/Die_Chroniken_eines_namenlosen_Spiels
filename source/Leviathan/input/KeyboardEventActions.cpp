#include "KeyboardEventActions.h"

namespace leviathan {
    namespace input {
        std::vector<Action> KeyboardEventActions::actionsFor(const irr::SEvent& event) {
            return createActions(event.KeyInput.Key, event.KeyInput.PressedDown);
        }
    }
}
