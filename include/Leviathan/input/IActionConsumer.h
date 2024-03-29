/*! \file IActionConsumer.h
 *  \brief Interface für Aktionen-Konsumenten.
 *  \note Bestandteil der Leviathan Engine
 */

#ifndef LEVIATHAN_PUBLIC_INTERFACES_INPUT_IACTIONCONSUMER_H
#define LEVIATHAN_PUBLIC_INTERFACES_INPUT_IACTIONCONSUMER_H

namespace leviathan {
    namespace input {
        struct Action;

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
