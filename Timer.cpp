#include "Timer.h"



Timer::Timer( const f32 maxValue )
: maxValue_(maxValue),
  currentValue_(0.0f),
  timerIsRunning_(false),
  timerIsPaused_(false)
{
    //
}



Timer::~Timer()
{
    // nothing to do here.
}



Timer* Timer::tick( const f32 frameDeltaTime )
{
    currentValue_ += frameDeltaTime;
    return this;
}



void Timer::start()
{
    timerIsPaused_ = false;
    timerIsRunning_ = true;
    currentValue_ = 0.0f;
}



void Timer::restart()
{
    start();
}



void Timer::stop()
{
    timerIsPaused_ = false;
    timerIsRunning_ = false;
    currentValue_ = 0.0f;
}



void Timer::pause()
{
    if ( timerIsRunning_ )
    {
        timerIsRunning_ = false;
        timerIsPaused_ = true;
    }
}



void Timer::resume()
{
    if ( timerIsPaused_ )
    {
        timerIsRunning_ = true;
        timerIsPaused_ = false;
    }
}



bool Timer::isRunning() const
{
    return timerIsRunning_;
}



bool Timer::isPaused() const
{
    return timerIsPaused_;
}



bool Timer::isFull() const
{
    return ( currentValue_ >= maxValue_ );
}



f32 Timer::getMaxValue() const
{
    return maxValue_;
}



/* private */
