/*! \file IActions.h
 *  \brief Bietet Mappings von beliebigen Eingaben zu in-Game Aktionen.
 *  \note Bestandteil der Leviathan Engine
 */

#ifndef LEVIATHAN_PUBLIC_INTERFACES_INPUT_IACTIONS_H
#define LEVIATHAN_PUBLIC_INTERFACES_INPUT_IACTIONS_H

#include <cstdint>

namespace leviathan {
    namespace input {
        struct IActionConsumer;

        /*! \interface IActions
         *  \brief Mappings von Inputs zu Aktionen
         */
        struct IActions {
            virtual ~IActions() {}

            /*! \brief Konsumenten von Aktionen können sich hier anmelden
             *  \param consumer: Konsument welcher bei seinen gewünschten Aktionen benachrichtigt werden soll
             *  \param id: ID der Aktion auf die der Konsument wartet
             */
            virtual void subscribe(IActionConsumer& consumer, const uint32_t id) = 0;

            /*! \brief Konsumenten von Aktionen können sich hier abmelden
             *  \param consumer: Konsument welcher sich abmelden möchte
             *  \param id: ID der Aktion von welcher der Konsument sich abmelden möchte
             */
            virtual void unsubscribe(IActionConsumer& consumer, const uint32_t id) = 0;

            /*! \brief Liest Aktionen und dazugehörige Eingaben aus einer Datei.
             *  \note Alle bereits vorhandene Aktionen werden entfernt.
             *  \note Tastatur-Codes gibt es unter anderem hier:
             *        https://docs.microsoft.com/en-gb/windows/win32/inputdev/virtual-key-codes?redirectedfrom=MSDN
             *  \param fileName: Mapping-Dateiname
             */
            virtual void loadFromFile(const char* fileName) = 0;
        };
    }
}

#endif
