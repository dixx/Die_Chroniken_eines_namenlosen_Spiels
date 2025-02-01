#include "EventReceiver.h"
#include <algorithm>
#include <cstdint>

namespace leviathan {
    namespace input {
        bool EventReceiver::OnEvent(const irr::SEvent& event) {
            if (mSubscriptions[event.EventType].size() == 0) return false;
            bool processed = false;
            // we iterate in reverse, because mSubscriptions can shrink while being iterated
            for (auto it = mSubscriptions[event.EventType].size(); it != 0; it--) {
                if (mSubscriptions[event.EventType][it - 1]->onEvent(event)) {
                    processed = true;
                }
            }
            return processed;
        }

        void EventReceiver::subscribe(input::IEventConsumer& consumer, const irr::EEVENT_TYPE eventType) {
            auto found = std::find(mSubscriptions[eventType].begin(), mSubscriptions[eventType].end(), &consumer);
            if (found == mSubscriptions[eventType].end()) {
                mSubscriptions[eventType].push_back(&consumer);
            }
        }

        void EventReceiver::unsubscribe(input::IEventConsumer& consumer, const irr::EEVENT_TYPE eventType) {
            auto found = std::find(mSubscriptions[eventType].begin(), mSubscriptions[eventType].end(), &consumer);
            if (found != mSubscriptions[eventType].end()) {
                mSubscriptions[eventType].erase(found);
            }
        }
    }
}
