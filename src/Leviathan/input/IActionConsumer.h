/*! \file IActionConsumer.h
 *  \brief Interface für Aktionen-Konsumenten.
 *  \note Bestandteil der Leviathan Engine
 */

#ifndef LEVIATHAN_INPUT_IACTIONCONSUMER_H
#define LEVIATHAN_INPUT_IACTIONCONSUMER_H

#include "Action.h"

namespace leviathan {
    namespace input {

        /*! \interface IActionConsumer
         *  \brief Interface für Konsumenten von Aktionen.
         */
        struct IActionConsumer {
            virtual ~IActionConsumer() {}

            /*! \brief Reagiert auf Aktionen.
             *  \param action: Aktion, gesendet vom Producer
             */
            virtual void onAction(const Action action) = 0;
        };
    }
}
#endif
