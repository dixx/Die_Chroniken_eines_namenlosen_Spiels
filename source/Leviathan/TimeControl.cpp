#include "TimeControl.h"

namespace leviathan
{
    namespace core
    {
        TimeControl::TimeControl()
        : timers_()
        {
        }

        void TimeControl::add(Timer& timer)
        {
            timers_.push_back(&timer);
        }

        void TimeControl::remove(Timer& timer)
        {
            for (auto& item : timers_)
            {
                if (item == &timer)
                {
                    timers_.remove(item);
                    break;
                }
            }
        }

        void TimeControl::pause()
        {
            for (auto& timer : timers_)
                timer->pause();
        }

        void TimeControl::resume()
        {
            for (auto& timer : timers_)
                timer->resume();
        }

        void TimeControl::tick(const float seconds)
        {
            for (auto& timer : timers_)
                timer->tick(seconds);
        }
    }
}
