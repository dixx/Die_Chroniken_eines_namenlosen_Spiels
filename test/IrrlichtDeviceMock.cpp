#include "IrrlichtDeviceMock.h"

IrrlichtDeviceMock::IrrlichtDeviceMock( irr::IrrlichtDevice* device )
: original_(device),
  timer_()
{
}

IrrlichtTimerMock* IrrlichtDeviceMock::getTimer()
{
    return &timer_;
}

bool IrrlichtDeviceMock::run()
{
    return false;
}

bool IrrlichtDeviceMock::isWindowActive()
{
    return false;
}

void IrrlichtDeviceMock::yield()
{
}
