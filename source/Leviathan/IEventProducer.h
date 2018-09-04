/*! \file IEventProducer.h
 *  \brief Interface für Event-Verteiler.
 *  \note Bestandteil der Leviathan Engine
 */

#ifndef LEVIATHAN_INPUT_IEVENTPRODUCER_H
#define LEVIATHAN_INPUT_IEVENTPRODUCER_H

#include "IEventConsumer.h"
#include "irrlicht.h"

namespace leviathan
{
    namespace input
    {
        /*! \interface IEventProducer
         *  \brief Interface für Verteiler von `irr::SEvent`s.
         */
        struct IEventProducer
        {
            virtual ~IEventProducer() {};

            /*! \brief Konsumenten von Events melden sich hier an.
             *  \param consumer: Konsument von Events
             *  \param eventType: Typ des Events (Mouse, Keyboard, ...)
             */
            virtual void subscribe(const IEventConsumer& consumer, irr::EEVENT_TYPE eventType) = 0;
        };
    }
}
#endif
