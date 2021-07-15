/*! \file Heroes.h
 *  \brief Erstellen und Verwalten von Helden.
 */

#ifndef LEVIATHAN_GAME_HEROES_H
#define LEVIATHAN_GAME_HEROES_H

#include "Hero.h"
#include <map>
#include <memory>
#include <string>

namespace leviathan {
    namespace world {
        class NodeManager;
    }

    namespace characters {
        struct CharacterConfiguration;

        /*! \class Heroes Heroes.h "Heroes.h"
         *  \brief Diese Klasse enthält Funktionen zum Erstellen und Verwalten von Helden.
         */
        class Heroes {
        public:
            /*! \brief Konstruktor
             *  \param nodeManager: Instanz der 3D-Szenenknoten-Verwaltung
             */
            explicit Heroes(world::NodeManager& nodeManager);

            ~Heroes() = default;
            Heroes(const Heroes&) = delete;
            Heroes& operator=(const Heroes&) = delete;

            /*! \brief Erzeugt einen neuen Helden und gibt ihn zurück.
             *  \param internalName: interner Name des neuen Helden
             */
            Hero& create(const CharacterConfiguration& characterConfig);

            /*! \brief Aktiviert den gewünschten Helden und deaktiviert den vorher aktiven Helden.
             *  \param internalName: interner Name des neuen Helden
             */
            void activate(const std::string& internalName);

            /*! \brief Gibt den aktiven Helden zurück.
             */
            Hero& getActiveHero();

        private:
            world::NodeManager& nodeManager_;
            std::map<std::string, std::unique_ptr<Hero>> heroes_ = std::map<std::string, std::unique_ptr<Hero>>();
            std::string activeHeroName_ = "";
        };
    }
}
#endif
