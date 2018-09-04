#ifndef _TESTHELPER_LEVIATHAN_DEVICE_HEADER
#define _TESTHELPER_LEVIATHAN_DEVICE_HEADER

#include "irrlicht.h"
#include "leviathan.h"

namespace TesthelperLeviathanDevice
{
    class LeviathanDeviceWithIrrlichtMock : public leviathan::LeviathanDevice
    {
    public:
        LeviathanDeviceWithIrrlichtMock();
        ~LeviathanDeviceWithIrrlichtMock();
        void injectMockedGraphicEngine(irr::IrrlichtDevice& mock);
        void restoreOriginalGraphicEngine();
        irr::IrrlichtDevice* getGraphicEngine();

    private:
        irr::IrrlichtDevice* originalGraphicEngine_;
        LeviathanDeviceWithIrrlichtMock(const LeviathanDeviceWithIrrlichtMock&);
        void operator=(const LeviathanDeviceWithIrrlichtMock&);
    };
}

#endif
