#include "EventReceiver.h"

namespace leviathan
{
    namespace core
    {
        EventReceiver::EventReceiver( leviathan::input::Keyboard& keyboard )
        : keyboard_(keyboard)
        {
        }

        EventReceiver::~EventReceiver()
        {
        }

        bool EventReceiver::OnEvent( const irr::SEvent& event )
        {
            if ( event.EventType == irr::EET_KEY_INPUT_EVENT )
            {
                keyboard_.setKeyState(
                    event.KeyInput.Key,
                    event.KeyInput.PressedDown,
                    event.KeyInput.Shift,
                    event.KeyInput.Control
                );
                return true;
            }
            return false;
        }
    }
}
