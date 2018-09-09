/*! \file Actions.h
 *  \brief Bietet Mappings von beliebigen Eingaben zu in-Game Aktionen.
 *  \note Bestandteil der Leviathan Engine
 */

#ifndef LEVIATHAN_ACTIONS_H
#define LEVIATHAN_ACTIONS_H

#include <cstdint>
#include <map>
#include <set>
#include <string>
#include <yaml-cpp/yaml.h>
#include "irrlicht.h"
#include "IActionConsumer.h"
#include "IEventProducer.h"
#include "IEventConsumer.h"

namespace leviathan
{
    namespace input
    {

        /*! \class Actions
         *  \brief Mapping von Input zu Aktion
         */
        class Actions : public IEventConsumer
        {

        public:

            /*! \brief Konstruktor.
             *  \param producer: produziert (versendet) Events
             */
            Actions(IEventProducer& producer);

            Actions() = delete;
            ~Actions() = default;
            Actions(const Actions&) = delete;
            Actions& operator=(const Actions&) = delete;

            /*! \brief Konsumenten von Aktionen können sich hier anmelden
             *  \param consumer: Konsument welcher bei seinen gewünschten Aktionen benachrichtigt werden soll
             *  \param id: ID der Aktion auf die der Konsument wartet
             */
            void subscribe(IActionConsumer& consumer, const uint32_t id);

            /*! \brief Konsumenten von Aktionen können sich hier abmelden
             *  \param consumer: Konsument welcher sich abmelden möchte
             *  \param id: ID der Aktion von welcher der Konsument sich abmelden möchte
             */
            void unsubscribe(IActionConsumer& consumer, const uint32_t id);

            /*! \brief Reagiert auf Events vom Producer.
             *  \param event: Input-Event
             */
            void onEvent(const irr::SEvent& event);

            /*! \brief Liest Aktionen und dazugehörige Eingaben aus einer Datei.
             *  \note Bereits vorhandene Aktionen werden mit denen aus der Datei überschrieben.
             *  \param fileName: Mapping-Dateiname
             */
            void mergeFromFile(const irr::io::path& fileName);

        private:
            struct Input {
                Input() {}; // std::map needs this
                explicit Input(const YAML::Node& node);
                std::string name = "- None -", type = "unknown";
                uint32_t id = 0;
                bool isActive = false, wasActive = false;
            };
            struct Action {
                Action() {}; // std::map needs this
                explicit Action(const YAML::Node& node);
                std::string name = "nameless action", description = "";
                uint32_t id = 0;
                bool internal = false;
                Input primary = Input(), secondary = Input();
            };
            std::map<uint32_t, Action> _actions = std::map<uint32_t, Action>();
            std::map<uint32_t, std::set<IActionConsumer*>> _subscriptions = std::map<uint32_t, std::set<IActionConsumer*>>();
            std::vector<std::map<uint32_t, uint32_t>> _converter = std::vector(2, std::map<uint32_t, uint32_t>());

            void addActionToConverter(const Action& action);
        };
    }
}

#endif
