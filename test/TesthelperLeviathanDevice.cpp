#include "TesthelperLeviathanDevice.h"

namespace TesthelperLeviathanDevice
{
    LeviathanDeviceWithIrrlichtMock::LeviathanDeviceWithIrrlichtMock()
    : originalGraphicEngine_(graphicEngine_),
      mockedGraphicEngine_(graphicEngine_)
    {
    }

    LeviathanDeviceWithIrrlichtMock::~LeviathanDeviceWithIrrlichtMock()
    {
        disableMock();
    }

    void LeviathanDeviceWithIrrlichtMock::enableMock()
    {
        graphicEngine_ = (irr::IrrlichtDevice*)(&mockedGraphicEngine_);
    }

    void LeviathanDeviceWithIrrlichtMock::disableMock()
    {
        graphicEngine_ = originalGraphicEngine_;
    }
}
