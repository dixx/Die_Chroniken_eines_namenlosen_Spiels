/*! \file Keyboard.h
 *  \brief Tastaturabfragen leicht gemacht
 *  \note Bestandteil der Leviathan Engine
 *        The code is based on version 1.2a of the MastEventReceiver code,
 *        © (Copyright) Robert E. Demarest, AKA Mastiff or Mastiff Odit. A thousand thanks to him!
 */

#ifndef _LEVIATHAN_KEYBOARD_HEADER
#define _LEVIATHAN_KEYBOARD_HEADER

#include <array>
#include <irrlicht.h>

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

            /*! \brief Destruktor.
             */
            ~Keyboard() = default;

            Keyboard( const Keyboard& ) = delete;
            Keyboard& operator=( const Keyboard& ) = delete;

            /*! \brief Speichert die letzten Tastenzustände.
             *
             *         Wichtig, um mit Veränderungen (Taste wurde gerade gedrückt/losgelassen) arbeiten zu können,
             *         da diese Zustandsänderungen über Events asynchron hier ankommen.
             */
            void update();

            /*! \brief Abfrage des aktuellen Zustands einer Taste.
             *  \param keyCode: Irrlicht Tastencode
             *  \return `true` wenn die Taste gedrückt ist, ansonsten `false`
             */
            bool isKeyDown( const irr::EKEY_CODE keycode ) const;

            /*! \brief Abfrage des vorherigen Zustands einer Taste.
             *  \param keyCode: Irrlicht Tastencode
             *  \return `true` wenn die Taste gedrückt ist, ansonsten `false`
             */
            bool wasKeyDown( const irr::EKEY_CODE keycode ) const;

            /*! \brief Abfrage der Änderung des Zustands einer Taste.
             *  \param keyCode: Irrlicht Tastencode
             *  \return `true` wenn die Taste gerade noch nicht gedrückt war und jetzt gedrückt ist, ansonsten `false`
             */
            bool hasKeyJustBeenSuppressed( const irr::EKEY_CODE keycode ) const;

            /*! \brief Abfrage der Änderung des Zustands einer Taste.
             *  \param keyCode: Irrlicht Tastencode
             *  \return `true` wenn die Taste gerade noch gedrückt war und jetzt nicht mehr gedrückt ist,
             *          ansonsten `false`
             */
            bool hasKeyJustBeenReleased( const irr::EKEY_CODE keycode ) const;

            /*! \brief Abfrage des aktuellen Zustands einer zusätzlich gedrückten SHIFT-Taste.
             *  \return `true` wenn irgendeine SHIFT-Taste gedrückt ist, ansonsten `false`
             */
            bool isShiftDown() const;

            /*! \brief Abfrage des vorherigen Zustands einer zusätzlich gedrückten SHIFT-Taste.
             *  \return `true` wenn eine SHIFT-Taste gedrückt war, ansonsten `false`
             */
            bool wasShiftDown() const;

            /*! \brief Abfrage des aktuellen Zustands einer zusätzlich gedrückten CTRL-Taste.
             *  \return `true` wenn irgendeine CTRL-Taste gedrückt ist, ansonsten `false`
             */
            bool isCtrlDown() const;

            /*! \brief Abfrage des vorherigen Zustands einer zusätzlich gedrückten CTRL-Taste.
             *  \return `true` wenn irgendeine CTRL-Taste gedrückt war, ansonsten `false`
             */
            bool wasCtrlDown() const;

            /*! \brief Speichert den aktuellen Zustand einer Taste.
             *  \note Diese Methode wird intern vom Eventreceiver verwendet.
             *  \param keyCode: Irrlicht Tastencode
             *  \param state: `true` wenn die Taste gedrückt ist, ansonsten `false`
             *  \param shiftState: `true` wenn Shift -wie auch immer- an ist, ansonsten `false`
             *  \param ctrlState: `true` wenn irgendein CTRL gedrückt ist, ansonsten `false`
             */
            void setKeyState( const irr::EKEY_CODE keycode, const bool state, const bool shiftState,
                const bool ctrlState );

        private:

            std::array<bool, irr::KEY_KEY_CODES_COUNT> keyIsDown_;
            std::array<bool, irr::KEY_KEY_CODES_COUNT> keyLastState_;
            bool shiftIsDown_;
            bool shiftWasDown_;
            bool ctrlIsDown_;
            bool ctrlWasDown_;
        };
    }
}

#endif
