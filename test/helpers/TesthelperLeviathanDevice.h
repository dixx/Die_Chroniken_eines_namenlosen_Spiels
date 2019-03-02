#ifndef HELPERS_TESTHELPER_LEVIATHAN_DEVICE_H
#define HELPERS_TESTHELPER_LEVIATHAN_DEVICE_H

#include "irrlicht.h"
#include "leviathan.h"

namespace TesthelperLeviathanDevice {
    class LeviathanDeviceWithIrrlichtMock : public leviathan::LeviathanDevice {
    public:
        explicit LeviathanDeviceWithIrrlichtMock(const irr::io::path& fileName);
        ~LeviathanDeviceWithIrrlichtMock();
        LeviathanDeviceWithIrrlichtMock() = delete;
        LeviathanDeviceWithIrrlichtMock(const LeviathanDeviceWithIrrlichtMock&) = delete;
        void operator=(const LeviathanDeviceWithIrrlichtMock&) = delete;
        void injectMockedGraphicEngine(irr::IrrlichtDevice& mock);
        void restoreOriginalGraphicEngine();
        irr::IrrlichtDevice* getGraphicEngine();

    private:
        irr::IrrlichtDevice* originalGraphicEngine_ = nullptr;
    };
}

#endif
