#include "GUIEventActions.h"
#include "IEventReceiver.h"
#include "IGUIElement.h"
#include <input/Action.h>

namespace leviathan {
    namespace input {
        std::vector<Action> GUIEventActions::actionsFor(const irr::SEvent& event) {
            if (event.GUIEvent.EventType == irr::gui::EGET_BUTTON_CLICKED)
                return createActions(event.GUIEvent.Caller->getName(), true);
            else
                return {};
        }

        std::list<uint32_t>& GUIEventActions::actionIdsFor(const std::string& inputName) {
            try {
                return mActionsForInput.at(inputName);
            } catch (const std::out_of_range& e) {
                return mEmptyList;
            }
        }

        void GUIEventActions::addMapping(const std::string inputName, const uint32_t actionId) {
            mActionsForInput[inputName].push_back(actionId);
            mActionsForInput[inputName].sort();
            mActionsForInput[inputName].unique();
        }

        std::vector<Action> GUIEventActions::createActions(const std::string& inputName, const bool isActive) {
            std::vector<Action> result;
            for (uint32_t actionId : actionIdsFor(inputName)) {
                result.push_back({actionId, isActive});
            }
            return result;
        }
    }
}
