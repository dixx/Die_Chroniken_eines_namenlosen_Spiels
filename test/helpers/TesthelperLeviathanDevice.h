#ifndef _TESTHELPER_LEVIATHAN_DEVICE_HEADER
#define _TESTHELPER_LEVIATHAN_DEVICE_HEADER

#include <irrlicht.h>
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
        irr::IrrlichtDevice* getGraphicEngine();
        void sendKeyboardEvent( const irr::EKEY_CODE keycode, const bool state, const bool shiftState,
            const bool ctrlState );
        void sendMouseEvent( const leviathan::input::Mouse::Button button, const bool buttonState, const int32_t x,
            const int32_t y, const float wheelDelta );
        void sendGUIEvent( const irr::gui::IGUIElement& caller, const irr::gui::EGUI_EVENT_TYPE eventType );

    private:
        irr::IrrlichtDevice* originalGraphicEngine_;
        LeviathanDeviceWithIrrlichtMock( const LeviathanDeviceWithIrrlichtMock& );
        void operator=( const LeviathanDeviceWithIrrlichtMock& );
    };
}

#endif
