#ifndef _IRRLICHT_DEVICE_MOCK_HEADER
#define _IRRLICHT_DEVICE_MOCK_HEADER

#include <irrlicht.h>
#include "IrrlichtTimerMock.h"

class IrrlichtDeviceMock
{
public:
    IrrlichtDeviceMock( irr::IrrlichtDevice* device );
    // mocked methods
    IrrlichtTimerMock* getTimer();
    bool run();
    bool isWindowActive();
    void yield();
private:
    irr::IrrlichtDevice* original_;
    IrrlichtTimerMock timer_;
};

#endif

// TODO this smells like a more generic mock class.
// - was method called?
// - what should method return?
// - what has been the arguments?
// - how to check mocks within mocks?
