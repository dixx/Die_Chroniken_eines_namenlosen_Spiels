#ifndef _TESTHELPER_LEVIATHAN_DEVICE_HEADER
#define _TESTHELPER_LEVIATHAN_DEVICE_HEADER

#include "leviathan.h"

namespace TesthelperLeviathanDevice
{
    class LeviathanDeviceWithIrrlichtMock : public leviathan::LeviathanDevice
    {
    public:
        LeviathanDeviceWithIrrlichtMock();
        ~LeviathanDeviceWithIrrlichtMock();
        void injectMockedGraphicEngine( irr::IrrlichtDevice& mock );
        void restoreOriginalGraphicEngine();

    private:
        irr::IrrlichtDevice* originalGraphicEngine_;
    };
}

#endif
