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

    void LeviathanDeviceWithIrrlichtMock::sendKeyboardEvent( const irr::EKEY_CODE keycode, const bool state,
        const bool shiftState, const bool ctrlState )
    {
        irr::SEvent event;
        event.EventType = irr::EET_KEY_INPUT_EVENT;
        event.KeyInput.Key = keycode;
        event.KeyInput.PressedDown = state;
        event.KeyInput.Shift = shiftState;
        event.KeyInput.Control = ctrlState;
        graphicEngine_->postEventFromUser( event );
    }
}
