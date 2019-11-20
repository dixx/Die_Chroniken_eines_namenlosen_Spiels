#include "EventReceiver.h"

namespace leviathan {
    namespace input {
        bool EventReceiver::OnEvent(const irr::SEvent& event) {
            bool processed = false;
            for (auto consumer : _subscriptions[event.EventType]) {
                if (consumer->onEvent(event)) {
                    processed = true;
                }
            }
            return processed;
        }

        void EventReceiver::subscribe(leviathan::input::IEventConsumer& consumer, const irr::EEVENT_TYPE eventType) {
            _subscriptions[eventType].insert(&consumer);
        }

        void EventReceiver::unsubscribe(leviathan::input::IEventConsumer& consumer, const irr::EEVENT_TYPE eventType) {
            _subscriptions[eventType].erase(&consumer);
        }
    }
}
