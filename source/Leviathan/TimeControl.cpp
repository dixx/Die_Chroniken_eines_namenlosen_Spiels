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
            for( itr_ = timerList_.begin(); itr_ != timerList_.end(); ++itr_ )
            {
                if( *itr_ == &timer )
                {
                    timerList_.erase( itr_ );
                    break;
                }
            }
        }

        void TimeControl::pause()
        {
            for( itr_ = timerList_.begin(); itr_ != timerList_.end(); ++itr_ )
                (*itr_)->pause();
        }

        void TimeControl::resume()
        {
            for( itr_ = timerList_.begin(); itr_ != timerList_.end(); ++itr_ )
                (*itr_)->resume();
        }

        void TimeControl::tick( const irr::f32 frameDeltaTime )
        {
            for( itr_ = timerList_.begin(); itr_ != timerList_.end(); ++itr_ )
                (*itr_)->tick( frameDeltaTime );
        }
    }
}
