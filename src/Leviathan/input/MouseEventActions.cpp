#include "MouseEventActions.h"
#include <input/Action.h>

namespace leviathan {
    namespace input {
        std::vector<Action> MouseEventActions::actionsFor(const irr::SEvent& event) {
            if (isLeftButton(event))
                return createActions(irr::EMBSM_LEFT, event.MouseInput.isLeftPressed());
            else if (isMiddleButton(event))
                return createActions(irr::EMBSM_MIDDLE, event.MouseInput.isMiddlePressed());
            else if (isRightButton(event))
                return createActions(irr::EMBSM_RIGHT, event.MouseInput.isRightPressed());
            else
                return {};
        }

        void MouseEventActions::addMapping(const uint32_t buttonCode, const uint32_t actionId) {
            _actionsForInput[buttonCode].push_back(actionId);
            _actionsForInput[buttonCode].sort();
            _actionsForInput[buttonCode].unique();
        }

        bool MouseEventActions::isLeftButton(const irr::SEvent& event) const {
            return event.MouseInput.Event == irr::EMIE_LMOUSE_PRESSED_DOWN
                   || event.MouseInput.Event == irr::EMIE_LMOUSE_LEFT_UP;
        }

        bool MouseEventActions::isMiddleButton(const irr::SEvent& event) const {
            return event.MouseInput.Event == irr::EMIE_MMOUSE_PRESSED_DOWN
                   || event.MouseInput.Event == irr::EMIE_MMOUSE_LEFT_UP;
        }

        bool MouseEventActions::isRightButton(const irr::SEvent& event) const {
            return event.MouseInput.Event == irr::EMIE_RMOUSE_PRESSED_DOWN
                   || event.MouseInput.Event == irr::EMIE_RMOUSE_LEFT_UP;
        }
    }
}
