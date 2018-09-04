/*! \file EventReceiver.h
 *  \brief Behandlung von Tastatur/Maus, GUI und anderen Events.
 *  \note Bestandteil der Leviathan Engine.
 *        The code here and in the Keyboard class is based on version 1.2a of the MastEventReceiver code,
 *        © (Copyright) Robert E. Demarest, AKA Mastiff or Mastiff Odit. A thousand thanks to him!
 */

#ifndef _LEVIATHAN_EVENTRECEIVER_HEADER
#define _LEVIATHAN_EVENTRECEIVER_HEADER

#include "irrlicht.h"
#include "GameStateManager.h"

namespace leviathan
{
    namespace core
    {

        /*! \class EventReceiver EventReceiver.h "EventReceiver.h"
         *  \brief Diese Klasse enthält Funktionen zum Behandeln von Events.
         */
        class EventReceiver : public irr::IEventReceiver
        {

        public:

            /*! \brief Konstruktor.
             */
            EventReceiver() = default;

            /*! Destruktor.
             */
            virtual ~EventReceiver() = default;

            EventReceiver(const EventReceiver&) = delete;
            EventReceiver& operator=(const EventReceiver&) = delete;

            /*! \brief Event-Handler.
             *
             *  Hier wird festgelegt, was bei einem beliebigen Tastatur-, Maus- oder GUI-Ereignis passieren soll.
             *  \attention Funktion wird im Hintergrund über Events bedient und sollte nicht aufgerufen werden!
             *  \param event: Event vom Betriebssystem oder sonstwo her.
             *  \return `true` wenn Event erfolgreich behandelt wurde, ansonsten `false`
             */
            bool OnEvent(const irr::SEvent& event) final;
        };
    }
}
#endif
