/*! \file Mouse.h
 *  \brief Mausabfragen leicht gemacht
 *  \note Bestandteil der Leviathan Engine
 *        The code is based on version 1.2a of the MastEventReceiver code,
 *        © (Copyright) Robert E. Demarest, AKA Mastiff or Mastiff Odit. A thousand thanks to him!
 */

#ifndef _LEVIATHAN_MOUSE_HEADER
#define _LEVIATHAN_MOUSE_HEADER

#include <array>
#include <cstdint>
#include <irrlicht.h>

namespace leviathan
{
    namespace input
    {

        /*! \class Mouse Mouse.h "Mouse.h"
         *  \brief Hilfsmethoden für Mausabfragen
         */
        class Mouse
        {

        public:

            /*! \brief Maustasten
             */
            enum Button {
                LEFT = 0,
                MIDDLE,
                RIGHT,
                COUNT
            };

            /*! \brief Konstruktor.
             */
            Mouse();

            Mouse( const Mouse& ) = delete;
            Mouse& operator=( const Mouse& ) = delete;

            /*! \brief Speichert die letzten Maustastenzustände.
             *
             *         Wichtig, um mit Veränderungen (Maustaste wurde gerade gedrückt/losgelassen) arbeiten zu können,
             *         da diese Zustandsänderungen über Events asynchron hier ankommen.
             */
            // void update();

            /*! \brief Abfrage des aktuellen Zustands der linken Maustaste.
             *  \return `true` wenn die Maustaste gedrückt ist, ansonsten `false`
             */
            bool isLMBDown() const;

            /*! \brief Abfrage des aktuellen Zustands der mittleren Maustaste.
             *  \return `true` wenn die Maustaste gedrückt ist, ansonsten `false`
             */
            bool isMMBDown() const;

            /*! \brief Abfrage des aktuellen Zustands der rechten Maustaste.
             *  \return `true` wenn die Maustaste gedrückt ist, ansonsten `false`
             */
            bool isRMBDown() const;

            /*! \brief Abfrage des vorherigen Zustands der linken Maustaste.
             *  \return `true` wenn die Maustaste gedrückt war, ansonsten `false`
             */
            bool wasLMBDown() const;

            /*! \brief Abfrage des vorherigen Zustands der mittleren Maustaste.
             *  \return `true` wenn die Maustaste gedrückt war, ansonsten `false`
             */
            bool wasMMBDown() const;

            /*! \brief Abfrage des vorherigen Zustands der rechten Maustaste.
             *  \return `true` wenn die Maustaste gedrückt war, ansonsten `false`
             */
            bool wasRMBDown() const;

            /*! \brief Abfrage der aktuellen Mauszeigerposition.
             *  \return 2D-Koordinaten der aktuellen Mauszeigerposition
             */
            const irr::core::position2di& getPosition() const;

            /*! \brief Abfrage der vorherigen Mauszeigerposition.
             *  \return 2D-Koordinaten der vorherigen Mauszeigerposition
             */
            const irr::core::position2di& getLastPosition() const;

            /*! \brief Abfrage der Mausrad-Richtungsänderung
             *  \return Richtungsänderung
             */
            float getWheelDelta() const;

            /*! \brief Speichert den aktuellen Zustand einer Maustaste.
             *  \note Diese Methode wird intern vom Eventreceiver verwendet.
             *  \param button: Maustaste
             *  \param state: `true` wenn die Taste gedrückt ist, ansonsten `false`
             */
            void setMouseButtonState( const Button button, const bool state );

            /*! \brief Speichert die aktuellen 2D-Koordinaten des Mauszeigers.
             *  \note Diese Methode wird intern vom Eventreceiver verwendet.
             *  \param x, y: 2D-Koordinaten des Mauszeigers
             */
            void setMouseCoordinateState( const int32_t x, const int32_t y );

            /*! \brief Speichert das aktuelle Mausrad-Delta.
             *  \note Diese Methode wird intern vom Eventreceiver verwendet.
             *  \param delta: Scrollrichtung und -Geschwindigkeit des Mausrades
             */
            void setMouseWheelState( const float delta );

        private:

            std::array<bool, Button::COUNT> buttonIsDown_;
            std::array<bool, Button::COUNT> buttonLastState_;
            irr::core::position2di position_;
            irr::core::position2di lastPosition_;
            float wheelData_;
        };
    }
}

#endif
