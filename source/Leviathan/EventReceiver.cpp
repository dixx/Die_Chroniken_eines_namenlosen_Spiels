#include "EventReceiver.h"

namespace leviathan
{
    namespace core
    {
        EventReceiver::EventReceiver( leviathan::input::Keyboard& keyboard, leviathan::input::Mouse& mouse,
            leviathan::core::GameStateManager& gameStateManager )
        : keyboard_(keyboard),
          mouse_(mouse),
          gameStateManager_(gameStateManager)
        {
        }

        EventReceiver::~EventReceiver()
        {
        }

        bool EventReceiver::OnEvent( const irr::SEvent& event )
        {
            if ( event.EventType == irr::EET_MOUSE_INPUT_EVENT )
                return handleMouseEvents( event );
            if ( event.EventType == irr::EET_KEY_INPUT_EVENT )
                return handleKeyboardEvents( event );
            if ( event.EventType == irr::EET_GUI_EVENT )
                return gameStateManager_.handleGuiEvent( event );
            return false;
        }

        bool EventReceiver::handleMouseEvents( const irr::SEvent& event )
        {
            switch ( event.MouseInput.Event )
            {
                case irr::EMIE_MOUSE_MOVED:
                    mouse_.setCoordinates( event.MouseInput.X, event.MouseInput.Y );
                    break;
                case irr::EMIE_LMOUSE_PRESSED_DOWN:
                    mouse_.setButtonState( input::Mouse::Button::LEFT, true );
                    break;
                case irr::EMIE_LMOUSE_LEFT_UP:
                    mouse_.setButtonState( input::Mouse::Button::LEFT, false );
                    break;
                case irr::EMIE_RMOUSE_PRESSED_DOWN:
                    mouse_.setButtonState( input::Mouse::Button::RIGHT, true );
                    break;
                case irr::EMIE_RMOUSE_LEFT_UP:
                    mouse_.setButtonState( input::Mouse::Button::RIGHT, false );
                    break;
                case irr::EMIE_MMOUSE_PRESSED_DOWN:
                    mouse_.setButtonState( input::Mouse::Button::MIDDLE, true );
                    break;
                case irr::EMIE_MMOUSE_LEFT_UP:
                    mouse_.setButtonState( input::Mouse::Button::MIDDLE, false );
                    break;
                case irr::EMIE_MOUSE_WHEEL:
                    mouse_.setWheelDelta( event.MouseInput.Wheel );
                    break;
                default:
                    return false;
            }
            return true;
        }

        bool EventReceiver::handleKeyboardEvents( const irr::SEvent& event )
        {
            keyboard_.setKeyState(
                event.KeyInput.Key,
                event.KeyInput.PressedDown,
                event.KeyInput.Shift,
                event.KeyInput.Control
            );
            return true;
        }
    }
}
