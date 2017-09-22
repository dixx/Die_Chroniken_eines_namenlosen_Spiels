#include "TesthelperLeviathanDevice.h"

namespace TesthelperLeviathanDevice
{
    LeviathanDeviceWithIrrlichtMock::LeviathanDeviceWithIrrlichtMock()
    : originalGraphicEngine_(0)
    {
    }

    LeviathanDeviceWithIrrlichtMock::~LeviathanDeviceWithIrrlichtMock()
    {
        restoreOriginalGraphicEngine();
    }

    void LeviathanDeviceWithIrrlichtMock::injectMockedGraphicEngine( irr::IrrlichtDevice& mock )
    {
        originalGraphicEngine_ = graphicEngine_; // graphicEngine_ may have been changed by parents init method
        graphicEngine_ = &mock;
    }

    void LeviathanDeviceWithIrrlichtMock::restoreOriginalGraphicEngine()
    {
        graphicEngine_ = originalGraphicEngine_;
    }

    irr::IrrlichtDevice* LeviathanDeviceWithIrrlichtMock::getGraphicEngine()
    {
        return graphicEngine_;
    }
}
