#include "EventReceiver.h"
#include <algorithm>
#include <cstdint>

namespace leviathan {
    namespace input {
        bool EventReceiver::OnEvent(const irr::SEvent& event) {
            if (_subscriptions[event.EventType].size() == 0) return false;
            bool processed = false;
            // we iterate in reverse, because _subscriptions can shrink while being iterated
            for (uint32_t it = _subscriptions[event.EventType].size(); it != 0; it--) {
                if (_subscriptions[event.EventType][it - 1]->onEvent(event)) { processed = true; }
            }
            return processed;
        }

        void EventReceiver::subscribe(leviathan::input::IEventConsumer& consumer, const irr::EEVENT_TYPE eventType) {
            auto found = std::find(_subscriptions[eventType].begin(), _subscriptions[eventType].end(), &consumer);
            if (found == _subscriptions[eventType].end()) { _subscriptions[eventType].push_back(&consumer); }
        }

        void EventReceiver::unsubscribe(leviathan::input::IEventConsumer& consumer, const irr::EEVENT_TYPE eventType) {
            auto found = std::find(_subscriptions[eventType].begin(), _subscriptions[eventType].end(), &consumer);
            if (found != _subscriptions[eventType].end()) { _subscriptions[eventType].erase(found); }
        }
    }
}
