/*! \file Actions.h
 *  \brief Bietet Mappings von beliebigen Eingaben zu in-Game Aktionen.
 *  \note Bestandteil der Leviathan Engine
 */

#ifndef _LEVIATHAN_ACTIONS_HEADER
#define _LEVIATHAN_ACTIONS_HEADER

#include <irrlicht.h>
#include <cstdint>
#include <map>
#include <string>
#include <yaml-cpp/yaml.h>

namespace leviathan
{
    namespace input
    {

        /*! \class Actions Actions.h "Actions.h"
         *  \brief Mapping von Input zu Aktion
         */
        class Actions
        {

        public:

            /*! \brief Konstruktor.
             */
            Actions();

            /*! \brief Destruktor.
             */
            ~Actions() = default;

            Actions(const Actions&) = delete;
            Actions& operator=(const Actions&) = delete;

            /*! \brief Passiert eine Aktion gerade?
             *  \param id: Identifikator einer Aktion
             *  \return `true` wenn die Aktion gerade passiert, ansonsten `false`
             */
            bool inProgress(uint32_t id) const;

            /*! \brief Passiert eine Aktion gerade nicht?
             *  \param id: Identifikator einer Aktion
             *  \return `true` wenn die Aktion gerade nicht passiert, ansonsten `false`
             */
            bool inactive(uint32_t id) const;

            /*! \brief Hat eine Aktion gerade erst begonnen?
             *  \param id: Identifikator einer Aktion
             *  \return `true` wenn die Aktion gerade erst begonnen hat, ansonsten `false`
             */
            bool justStarted(uint32_t id) const;

            /*! \brief Hat eine Aktion gerade erst aufgehört?
             *  \param id: Identifikator einer Aktion
             *  \return `true` wenn die Aktion gerade erst aufgehört hat, ansonsten `false`
             */
            bool justStopped(uint32_t id) const;

            /*! \brief Liest Aktionen und dazugehörige Eingaben aus einer Datei.
             *  \note Bereits vorhandene Aktionen werden mit denen aus der Datei überschrieben.
             *  \param fileName: Mapping-Dateiname
             */
            void mergeFromFile(const irr::io::path& fileName);

        private:

            struct Input {
                Input(); // std::map needs this
                explicit Input(const YAML::Node& node);
                std::string name, type;
                uint32_t id;
                bool isActive, wasActive;
            };
            struct Action {
                Action(); // std::map needs this
                explicit Action(const YAML::Node& node);
                std::string name, description;
                uint32_t id;
                Input primary, secondary;
            };
            std::map<uint32_t, Action> _custom;
            std::map<uint32_t, Action> _internal;
            const Action& getAction(const uint32_t id) const;
        };
    }
}

#endif
