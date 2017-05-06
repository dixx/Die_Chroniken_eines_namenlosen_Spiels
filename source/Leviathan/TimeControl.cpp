#include "TimeControl.h"

namespace leviathan
{
    namespace core
    {
        TimeControl::~TimeControl()
        {
            timerList_.clear();
        }

        void TimeControl::add( Timer& timer )
        {
            timerList_.push_back( &timer );
        }

        void TimeControl::remove( Timer& timer )
        {
            for( auto itr = timerList_.begin(); itr != timerList_.end(); ++itr )
            {
                if( *itr == &timer )
                {
                    timerList_.erase( itr );
                    break;
                }
            }
        }

        void TimeControl::pause()
        {
            for( auto& timer : timerList_ )
                timer->pause();
        }

        void TimeControl::resume()
        {
            for( auto& timer : timerList_ )
                timer->resume();
        }

        void TimeControl::tick( const irr::f32 frameDeltaTime )
        {
            for( auto& timer : timerList_ )
                timer->tick( frameDeltaTime );
        }
    }
}
