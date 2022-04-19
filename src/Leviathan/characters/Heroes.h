/*! \file Heroes.h
 *  \brief Erstellen und Verwalten von Helden.
 */

#ifndef LEVIATHAN_CHARACTERS_HEROES_H
#define LEVIATHAN_CHARACTERS_HEROES_H

#include "Hero.h"
#include <characters/IHeroes.h>
#include <map>
#include <memory>
#include <string>

namespace leviathan {
    namespace world {
        class NodeManager;
    }

    namespace characters {
        struct CharacterConfiguration;
        struct IHero;

        /*! \class Heroes Heroes.h "Heroes.h"
         *  \brief Diese Klasse enthält Funktionen zum Erstellen und Verwalten von Helden.
         */
        class Heroes final : public IHeroes {
        public:
            /*! \brief Konstruktor
             *  \param nodeManager: Instanz der 3D-Szenenknoten-Verwaltung
             */
            explicit Heroes(world::NodeManager& nodeManager);

            ~Heroes() = default;

            Heroes() = delete;
            Heroes(const Heroes&) = delete;
            Heroes(const Heroes&&) = delete;
            Heroes& operator=(const Heroes&) = delete;
            Heroes& operator=(const Heroes&&) = delete;

            /*! \brief Erzeugt einen neuen Helden und gibt ihn zurück.
             *  \param characterConfig: Konfiguration des Helden-Szenenknotens
             */
            IHero& create(const CharacterConfiguration& characterConfig) override;

            /*! \brief Aktiviert den gewünschten Helden und deaktiviert den vorher aktiven Helden.
             *  \param internalName: interner Name des neuen Helden
             */
            void activate(const std::string& internalName) override;

            /*! \brief Gibt den aktiven Helden zurück.
             */
            IHero& getActiveHero() override;

        private:
            world::NodeManager& nodeManager_;
            std::map<std::string, std::unique_ptr<Hero>> heroes_ = std::map<std::string, std::unique_ptr<Hero>>();
            std::string activeHeroName_ = "";
        };
    }
}
#endif
