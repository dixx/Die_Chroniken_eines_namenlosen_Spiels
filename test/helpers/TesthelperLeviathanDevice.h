#ifndef _TESTHELPER_LEVIATHAN_DEVICE_HEADER
#define _TESTHELPER_LEVIATHAN_DEVICE_HEADER

#include "leviathan.h"
#include "mocks/IrrlichtDeviceMock.h"

namespace TesthelperLeviathanDevice
{
    class LeviathanDeviceWithIrrlichtMock : public leviathan::LeviathanDevice
    {
    public:
        IrrlichtDeviceMock mockedGraphicEngine;

        LeviathanDeviceWithIrrlichtMock();
        ~LeviathanDeviceWithIrrlichtMock();
        void enableMock();
        void disableMock();

    private:
        irr::IrrlichtDevice* originalGraphicEngine_;
    };
}

#endif
