/*! \file EventReceiver.h
 *  \brief Behandlung von Tastatur/Maus, GUI und anderen Events.
 *  \note Bestandteil der Leviathan Engine.
 */

#ifndef LEVIATHAN_CORE_EVENTRECEIVER_H
#define LEVIATHAN_CORE_EVENTRECEIVER_H

#include "IEventConsumer.h"
#include "IEventProducer.h"
#include "irrlicht.h"
#include <map>
#include <vector>

namespace leviathan {
    namespace input {

        /*! \class EventReceiver EventReceiver.h "EventReceiver.h"
         *  \brief Diese Klasse enthält Funktionen zum Behandeln von Events.
         */
        class EventReceiver final : public irr::IEventReceiver, public leviathan::input::IEventProducer {
        public:
            /*! \brief Konstruktor.
             */
            EventReceiver() = default;

            /*! Destruktor.
             */
            ~EventReceiver() = default;

            EventReceiver(const EventReceiver&) = delete;
            EventReceiver& operator=(const EventReceiver&) = delete;

            /*! \brief Event-Handler.
             *
             *  Hier wird festgelegt, was bei einem beliebigen Tastatur-, Maus- oder GUI-Ereignis passieren soll.
             *  \attention Funktion wird im Hintergrund über Events bedient und sollte nicht aufgerufen werden!
             *  \param event: Event vom Betriebssystem oder sonstwo her.
             *  \return `true` wenn Event von mindestens einem Empfänger erfolgreich behandelt wurde, ansonsten `false`
             */
            bool OnEvent(const irr::SEvent& event);

            /*! \brief Anmeldung für Event-Empfänger.
             *
             *  Empfänger melden sich hier mit dem jeweiligen Event-Typ an, den sie empfangen wollen.
             *  \param consumer: Empfänger, an den Events weitergeleitet werden sollen
             *  \param eventType: Typ der Events, die weitergeleitet werden sollen
             */
            void subscribe(leviathan::input::IEventConsumer& consumer, const irr::EEVENT_TYPE eventType);

            /*! \brief Abmeldung von Event-Empfängern.
             *
             *  Empfänger melden sich hier für den jeweiligen Event-Typ ab, den sie nicht mehr empfangen wollen.
             *  \param consumer: Empfänger, an den Events nicht mehr weitergeleitet werden sollen
             *  \param eventType: Typ der Events, die nicht mehr weitergeleitet werden sollen
             */
            void unsubscribe(leviathan::input::IEventConsumer& consumer, const irr::EEVENT_TYPE eventType);

        private:
            std::map<irr::EEVENT_TYPE, std::vector<leviathan::input::IEventConsumer*>> _subscriptions =
                std::map<irr::EEVENT_TYPE, std::vector<leviathan::input::IEventConsumer*>>();
        };
    }
}
#endif
