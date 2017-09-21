/*! \file Keyboard.h
 *  \brief Tastaturabfragen leicht gemacht
 *  \note Bestandteil der Leviathan Engine
 */

#ifndef _LEVIATHAN_KEYBOARD_HEADER
#define _LEVIATHAN_KEYBOARD_HEADER

#include <array>
#include <cstdint>

namespace leviathan
{
    namespace input
    {

        /*! \class Keyboard Keyboard.h "Keyboard.h"
         *  \brief Hilfsmethoden für Tastaturabfragen
         */
        class Keyboard
        {

        public:

            /*! \brief Konstruktor.
             */
            Keyboard();

            Keyboard( const Keyboard& ) = delete;
            Keyboard& operator=( const Keyboard& ) = delete;

            /*! \brief Erhöht den Timer um bestimmten Wert (in Sekunden).
             *  \param seconds: Zeit (in Sekunden)
             *  \return Referenz auf sich selbst
             */
             bool isKeyDown( const uint8_t keycode ) const;
             bool wasKeyDown( const uint8_t keycode ) const;
             bool hasKeyJustBeenSuppressed( const uint8_t keycode ) const;
             bool hasKeyJustBeenReleased( const uint8_t keycode ) const;
            //  bool isShiftDown() const;
            //  bool wasShiftDown() const;
            //  bool isCtrlDown() const;
            //  bool wasCtrlDown() const;
             void update();
             void setKeyState( const uint8_t keycode, const bool state );

        private:

            std::array<bool, 256> keyIsDown_;
            std::array<bool, 256> keyLastState_;
        };
    }
}

#endif
