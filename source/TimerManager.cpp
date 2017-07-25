#include "TimerManager.h"
#include "Logfile.h"



TimerManager& TimerManager::getInstance()
{
    static TimerManager instance;
    return instance;
}



leviathan::core::Timer* TimerManager::createTimer( const irr::f32 maxValue )
{
    timerList_.push_back( new leviathan::core::Timer( maxValue ) );
    timerCount_++;
    return *(timerList_.getLast());
}



void TimerManager::removeTimer( leviathan::core::Timer* timerToRemove )
{
    for( itr_ = timerList_.begin(); itr_ != timerList_.end(); ++itr_ )
    {
        if( *itr_ == timerToRemove )
        {
            delete timerToRemove;
            timerList_.erase( itr_ );
            break;
        }
    }
}



void TimerManager::pause()
{
    for( itr_ = timerList_.begin(); itr_ != timerList_.end(); ++itr_ )
        (*itr_)->pause();
}



void TimerManager::resume()
{
    for( itr_ = timerList_.begin(); itr_ != timerList_.end(); ++itr_ )
        (*itr_)->resume();
}



void TimerManager::tick( const irr::f32 frameDeltaTime )
{
    for( itr_ = timerList_.begin(); itr_ != timerList_.end(); ++itr_ )
        (*itr_)->tick( frameDeltaTime );
}



/* private */



TimerManager::TimerManager()
: timerList_(),
  itr_(),
  timerCount_(0),
  isPaused_(false)
{
	timerList_.clear();
    itr_ = timerList_.begin();
}



TimerManager::~TimerManager()
{
    // Niemals droppen, wenn Objekt nicht durch "create" erzeugt wurde!
    for( itr_ = timerList_.begin(); itr_ != timerList_.end(); ++itr_ )
    {
        delete *itr_;
        *itr_ = 0;
    }
    timerList_.clear();
}
