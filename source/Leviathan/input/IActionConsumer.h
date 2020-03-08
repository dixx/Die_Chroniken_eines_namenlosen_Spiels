/*! \file IActionConsumer.h
 *  \brief Interface für Aktionen-Konsumenten.
 *  \note Bestandteil der Leviathan Engine
 */

#ifndef LEVIATHAN_INPUT_IACTIONCONSUMER_H
#define LEVIATHAN_INPUT_IACTIONCONSUMER_H

#include <cstdint>

namespace leviathan {
    namespace input {

        /*! \interface IActionConsumer
         *  \brief Interface für Konsumenten von Aktionen.
         */
        struct IActionConsumer {
            virtual ~IActionConsumer() {}

            /*! \brief Reagiert auf Aktionen.
             *  \param id: ID der Aktion
             *  \param isActive: `true` wenn die Aktion gerade läuft, ansonsten `false`
             */
            virtual void onAction(const uint32_t id, const bool isActive) = 0;
        };
    }
}
#endif
