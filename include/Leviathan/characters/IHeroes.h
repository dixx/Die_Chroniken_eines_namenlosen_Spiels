/*! \file IHeroes.h
 *  \brief Erstellen und Verwalten von Helden.
 */

#ifndef LEVIATHAN_PUBLIC_INTERFACES_CHARACTERS_HEROES_H
#define LEVIATHAN_PUBLIC_INTERFACES_CHARACTERS_HEROES_H

#include <characters/CharacterConfiguration.h>
#include <characters/IHero.h>
#include <string>

namespace leviathan {
    namespace characters {
        /*! \interface IHeroes
         *  \brief Bietet Zugriff auf Funktionen zum Erstellen und Verwalten von Helden.
         */
        struct IHeroes {
            virtual ~IHeroes() {}

            /*! \brief Erzeugt einen neuen Helden und gibt ihn zurück.
             *  \param characterConfig: Konfiguration des Helden-Szenenknotens
             */
            virtual IHero& create(const CharacterConfiguration& characterConfig) = 0;

            /*! \brief Aktiviert den gewünschten Helden und deaktiviert den vorher aktiven Helden.
             *  \param internalName: interner Name des neuen Helden
             */
            virtual void activate(const std::string& internalName) = 0;

            /*! \brief Gibt den aktiven Helden zurück.
             */
            virtual IHero& getActiveHero() = 0;
        };
    }
}
#endif
