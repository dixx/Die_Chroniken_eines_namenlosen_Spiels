#ifndef _IRRLICHT_TIMER_MOCK_HEADER
#define _IRRLICHT_TIMER_MOCK_HEADER

#include <irrlicht.h>

class IrrlichtTimerMock
{
public:
    irr::u32 getTime();
};

#endif

// TODO this smells like a more generic mock class.
// - was method called?
// - what should method return?
// - what has been the arguments?
// - how to check mocks within mocks?
