/*! \file IEventConsumer.h
 *  \brief Interface für Event-Konsumenten.
 *  \note Bestandteil der Leviathan Engine
 */

#ifndef LEVIATHAN_INPUT_IEVENTCONSUMER_H
#define LEVIATHAN_INPUT_IEVENTCONSUMER_H

#include "irrlicht.h"

namespace leviathan
{
    namespace input
    {
        /*! \interface IEventConsumer
        *  \brief Interface für Konsumenten von `irr::SEvent`s.
         */
        struct IEventConsumer
        {
            virtual ~IEventConsumer() {};

            /*! \brief Kann von einem Producer mit Events bedient werden, sobald sie auftreten.
             *  \param event: beliebiges Event, z.B. Keyboard-Tastendruck
             *  \return `true` wenn Event erfolgreich behandelt wurde, ansonsten `false`
             */
            virtual bool onEvent(const irr::SEvent& event) = 0;
        };
    }
}
#endif
