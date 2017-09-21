#include "Keyboard.h"

namespace leviathan
{
    namespace input
    {
        Keyboard::Keyboard()
        : keyIsDown_(),
          keyLastState_()
        {
            keyIsDown_.fill( false );
            keyLastState_.fill( false );
        }

        bool Keyboard::isKeyDown( const uint8_t keycode ) const
        {
            return keyIsDown_[ keycode ];
        }

        bool Keyboard::wasKeyDown( const uint8_t keycode ) const
        {
            return keyLastState_[ keycode ];
        }

        bool Keyboard::hasKeyJustBeenSuppressed( const uint8_t keycode ) const
        {
            return ( isKeyDown( keycode ) && !wasKeyDown( keycode ) );
        }

        bool Keyboard::hasKeyJustBeenReleased( const uint8_t keycode ) const
        {
            return ( !isKeyDown( keycode ) && wasKeyDown( keycode ) );
        }

        // bool Keyboard::isShiftDown() const
        // {
        //     return false;
        // }
        //
        // bool Keyboard::wasShiftDown() const
        // {
        //     return false;
        // }
        //
        // bool Keyboard::isCtrlDown() const
        // {
        //     return false;
        // }
        //
        // bool Keyboard::wasCtrlDown() const
        // {
        //     return false;
        // }

        void Keyboard::update()
        {
            keyLastState_ = keyIsDown_;
        }

        void Keyboard::setKeyState( const uint8_t keycode, const bool state )
        {
            keyIsDown_[ keycode ] = state;
        }
    }
}
