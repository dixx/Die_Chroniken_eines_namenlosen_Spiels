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

    void LeviathanDeviceWithIrrlichtMock::sendMouseEvent( const leviathan::input::Mouse::Button button,
        const bool buttonState, const int32_t x, const int32_t y, const float wheelDelta )
    {
        irr::SEvent event;
        event.EventType = irr::EET_MOUSE_INPUT_EVENT;
        event.MouseInput.X = x;
        event.MouseInput.Y = y;
        event.MouseInput.Event = irr::EMIE_MOUSE_MOVED;
        graphicEngine_->postEventFromUser( event );
        event.MouseInput.Wheel = wheelDelta;
        event.MouseInput.Event = irr::EMIE_MOUSE_WHEEL;
        graphicEngine_->postEventFromUser( event );
        if( button == leviathan::input::Mouse::Button::LEFT )
            event.MouseInput.Event = buttonState ? irr::EMIE_LMOUSE_PRESSED_DOWN : irr::EMIE_LMOUSE_LEFT_UP;
        if( button == leviathan::input::Mouse::Button::MIDDLE )
            event.MouseInput.Event = buttonState ? irr::EMIE_MMOUSE_PRESSED_DOWN : irr::EMIE_MMOUSE_LEFT_UP;
        if( button == leviathan::input::Mouse::Button::RIGHT )
            event.MouseInput.Event = buttonState ? irr::EMIE_RMOUSE_PRESSED_DOWN : irr::EMIE_RMOUSE_LEFT_UP;
        graphicEngine_->postEventFromUser( event );
    }

    void LeviathanDeviceWithIrrlichtMock::sendGUIEvent( const irr::gui::IGUIElement& caller,
        const irr::gui::EGUI_EVENT_TYPE eventType )
    {
        irr::SEvent event;
        event.EventType = irr::EET_GUI_EVENT;
        event.GUIEvent.caller = caller;
        event.GUIEvent.EventType = eventType;
        graphicEngine_->postEventFromUser( event );
    }
}
