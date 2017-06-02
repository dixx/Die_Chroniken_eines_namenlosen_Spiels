#include "TesthelperLeviathanDevice.h"

namespace TesthelperLeviathanDevice
{
    LeviathanDeviceWithIrrlichtMock::LeviathanDeviceWithIrrlichtMock()
    : mockedGraphicEngine(),
      originalGraphicEngine_(0)
    {
    }

    LeviathanDeviceWithIrrlichtMock::~LeviathanDeviceWithIrrlichtMock()
    {
        disableMock();
    }

    void LeviathanDeviceWithIrrlichtMock::enableMock()
    {
        originalGraphicEngine_ = graphicEngine_; // graphicEngine_ may have been changed by parents init method
        graphicEngine_ = (irr::IrrlichtDevice*)(&mockedGraphicEngine);
    }

    void LeviathanDeviceWithIrrlichtMock::disableMock()
    {
        graphicEngine_ = originalGraphicEngine_;
    }
}
