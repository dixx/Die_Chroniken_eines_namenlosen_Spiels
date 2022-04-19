/*! \file Actions.h
 *  \brief Bietet Mappings von beliebigen Eingaben zu in-Game Aktionen.
 *  \note Bestandteil der Leviathan Engine
 */

#ifndef LEVIATHAN_INPUT_ACTIONS_H
#define LEVIATHAN_INPUT_ACTIONS_H

#include "GUIEventActions.h"
#include "IEventConsumer.h"
#include "KeyboardEventActions.h"
#include "MouseEventActions.h"
#include <cstdint>
#include <input/IActionConsumer.h>
#include <input/IActions.h>
#include <map>
#include <string>
#include <vector>

namespace irr {
    struct SEvent;
}

namespace leviathan {
    namespace core {
        struct ILogger;
    }

    namespace input {
        struct Action;
        struct IEventProducer;
        struct Input;

        /*! \class Actions
         *  \brief Mapping von Input zu Aktion
         */
        class Actions final : public IEventConsumer, public IActions {
        public:
            /*! \brief Konstruktor.
             *  \param producer: produziert (versendet) Events
             *  \param logger: Instanz eines Loggers
             */
            Actions(IEventProducer& producer, core::ILogger& logger);

            ~Actions();

            Actions() = delete;
            Actions(const Actions&) = delete;
            Actions(const Actions&&) = delete;
            Actions& operator=(const Actions&) = delete;
            Actions& operator=(const Actions&&) = delete;

            /*! \brief Konsumenten von Aktionen können sich hier anmelden
             *  \param consumer: Konsument welcher bei seinen gewünschten Aktionen benachrichtigt werden soll
             *  \param id: ID der Aktion auf die der Konsument wartet
             */
            void subscribe(IActionConsumer& consumer, const uint32_t id) override;

            /*! \brief Konsumenten von Aktionen können sich hier abmelden
             *  \param consumer: Konsument welcher sich abmelden möchte
             *  \param id: ID der Aktion von welcher der Konsument sich abmelden möchte
             */
            void unsubscribe(IActionConsumer& consumer, const uint32_t id) override;

            /*! \brief Reagiert auf Events vom Producer.
             *  \param event: Input-Event
             *  \return `true` wenn es zu diesem Event eine Aktion mit mindestens einem Empfänger gibt, ansonsten
             *          `false`
             */
            bool onEvent(const irr::SEvent& event);

            /*! \brief Liest Aktionen und dazugehörige Eingaben aus einer Datei.
             *  \note Alle bereits vorhandene Aktionen werden entfernt.
             *  \note Tastatur-Codes gibt es unter anderem hier:
             *        https://docs.microsoft.com/en-gb/windows/win32/inputdev/virtual-key-codes?redirectedfrom=MSDN
             *  \param fileName: Mapping-Dateiname
             */
            void loadFromFile(const char* fileName) override;

        private:
            core::ILogger& _logger;
            input::IEventProducer& _producer;
            std::map<uint32_t, std::vector<IActionConsumer*>> _subscriptions =
                std::map<uint32_t, std::vector<IActionConsumer*>>();
            MouseEventActions _mouseConverter = MouseEventActions();
            KeyboardEventActions _keyboardConverter = KeyboardEventActions();
            GUIEventActions _guiConverter = GUIEventActions();

            void addMapping(const uint32_t actionId, const Input& input);
            void dispatchActions(const std::vector<Action>& actions);
            EventToActionConverter* converter(const uint32_t eventType);
        };
    }
}

#endif
