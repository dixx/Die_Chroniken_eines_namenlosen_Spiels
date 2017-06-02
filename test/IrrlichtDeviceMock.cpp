#include "IrrlichtDeviceMock.h"

IrrlichtDeviceMock::IrrlichtDeviceMock()
: timer_(),
  runReturn_(),
  runReturnDefault_(false),
  runCallCount_(0),
  isWindowActiveReturn_(),
  isWindowActiveReturnDefault_(true), // TODO write setter for this
  isWindowActiveCallCount_(0),
  yieldCallCount_(0)
{
}

IrrlichtDeviceMock::~IrrlichtDeviceMock()
{
}

irr::ITimer* IrrlichtDeviceMock::getTimer()
{
    return (irr::ITimer*)(&timer_);
}

bool IrrlichtDeviceMock::run()
{
    runCallCount_++;
    if ( runReturn_.empty() )
    {
        return runReturnDefault_;
    }
    auto first = runReturn_.begin();
    bool ret = *first;
    runReturn_.erase( first );
    return ret;
}

void IrrlichtDeviceMock::letRunReturn( bool ret )
{
    runReturn_.push_back( ret );
}

irr::u32 IrrlichtDeviceMock::timesRunWasCalled()
{
    return runCallCount_;
}

bool IrrlichtDeviceMock::isWindowActive() const
{
    isWindowActiveCallCount_++;
    if ( isWindowActiveReturn_.empty() )
    {
        return isWindowActiveReturnDefault_;
    }
    auto first = isWindowActiveReturn_.begin();
    bool ret = *first;
    isWindowActiveReturn_.erase( first );
    return ret;
}

void IrrlichtDeviceMock::letIsWindowActiveReturn( bool ret )
{
    isWindowActiveReturn_.push_back( ret );
}

irr::u32 IrrlichtDeviceMock::timesIsWindowActiveWasCalled()
{
    return isWindowActiveCallCount_;
}

void IrrlichtDeviceMock::yield()
{
    yieldCallCount_++;
}

irr::u32 IrrlichtDeviceMock::timesYieldWasCalled()
{
    return yieldCallCount_;
}
