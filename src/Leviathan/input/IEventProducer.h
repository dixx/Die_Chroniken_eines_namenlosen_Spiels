/*! \file IEventProducer.h
 *  \brief Interface für Event-Verteiler.
 *  \note Bestandteil der Leviathan Engine
 */

#ifndef LEVIATHAN_INPUT_IEVENTPRODUCER_H
#define LEVIATHAN_INPUT_IEVENTPRODUCER_H

#include "IEventReceiver.h"

namespace leviathan {
    namespace input {
        struct IEventConsumer;

        /*! \interface IEventProducer
         *  \brief Interface für Verteiler von `irr::SEvent`s.
         */
        struct IEventProducer {
            virtual ~IEventProducer() {}

            /*! \brief Konsumenten von Events melden sich hier an.
             *  \param consumer: Konsument von Events
             *  \param eventType: Typ des Events (Mouse, Keyboard, ...)
             */
            virtual void subscribe(IEventConsumer& consumer, const irr::EEVENT_TYPE eventType) = 0;

            /*! \brief Konsumenten von Events melden sich hier ab.
             *  \param consumer: Konsument von Events
             *  \param eventType: Typ des Events (Mouse, Keyboard, ...)
             */
            virtual void unsubscribe(IEventConsumer& consumer, const irr::EEVENT_TYPE eventType) = 0;
        };
    }
}
#endif
