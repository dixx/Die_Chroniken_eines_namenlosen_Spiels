#include "MouseEventActions.h"

namespace leviathan {
    namespace input {
        std::vector<Action> MouseEventActions::actionsFor(const irr::SEvent& event) {
            switch (event.MouseInput.Event) {
            case irr::EMIE_LMOUSE_PRESSED_DOWN:
            case irr::EMIE_LMOUSE_LEFT_UP:
                return createActions(irr::EMBSM_LEFT, event.MouseInput.isLeftPressed());
            case irr::EMIE_RMOUSE_PRESSED_DOWN:
            case irr::EMIE_RMOUSE_LEFT_UP:
                return createActions(irr::EMBSM_RIGHT, event.MouseInput.isRightPressed());
            case irr::EMIE_MMOUSE_PRESSED_DOWN:
            case irr::EMIE_MMOUSE_LEFT_UP:
                return createActions(irr::EMBSM_MIDDLE, event.MouseInput.isMiddlePressed());
            default:
                return {};
            }
        }
    }
}
