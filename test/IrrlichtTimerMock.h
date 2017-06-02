#ifndef _IRRLICHT_TIMER_MOCK_HEADER
#define _IRRLICHT_TIMER_MOCK_HEADER

#include <irrlicht.h>

class IrrlichtTimerMock : public irr::ITimer
{
public:
    // mocked methods
    virtual irr::u32 getTime() const;
    // setter for mocked method return values; these can be called multiple times for sequential returns
    // getter for how many times mocked method was called so far
    // so far unused methods
    virtual irr::u32 getRealTime() const { return 0; };
    virtual irr::ITimer::RealTimeDate getRealTimeAndDate() const { return irr::ITimer::RealTimeDate(); };
    virtual void setTime(irr::u32 time) { (void)time; };
    virtual void stop() {};
    virtual void start() {};
    virtual void setSpeed(irr::f32 speed = 1.0f) { (void)speed; };
    virtual irr::f32 getSpeed() const { return 0.0f; };
    virtual bool isStopped() const { return false; };
    virtual void tick() {};
};

#endif

// TODO this smells like a more generic mock class.
// - was method called?
// - what should method return?
// - what has been the arguments?
// - how to check mocks within mocks?
