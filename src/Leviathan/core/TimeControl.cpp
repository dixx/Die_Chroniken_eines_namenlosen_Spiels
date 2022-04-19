#include "TimeControl.h"

namespace leviathan {
    namespace core {
        void TimeControl::add(Timer& timer) {
            mTimers.push_back(&timer);
        }

        void TimeControl::remove(Timer& timer) {
            for (auto& item : mTimers) {
                if (item == &timer) {
                    mTimers.remove(item);
                    break;
                }
            }
        }

        void TimeControl::pause() {
            for (auto& timer : mTimers)
                timer->pause();
        }

        void TimeControl::resume() {
            for (auto& timer : mTimers)
                timer->resume();
        }

        void TimeControl::tick(const float seconds) {
            for (auto& timer : mTimers)
                timer->tick(seconds);
        }
    }
}
