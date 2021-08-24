/*! \file IGround.h
 *  \brief Bietet Zugriff auf begehbaren Boden.
 *  \note Bestandteil der Leviathan Engine
 */

#ifndef LEVIATHAN_PUBLIC_INTERFACES_WORLD_IGROUND_H
#define LEVIATHAN_PUBLIC_INTERFACES_WORLD_IGROUND_H

namespace leviathan {
    namespace world {
        struct Node3DConfiguration;

        /*! \interface IGround
         *  \brief Bietet Zugriff auf begehbaren Boden
         */
        struct IGround {
            virtual ~IGround() {}

            /*! \brief Fügt ein Kartenteil hinzu.
             *  \param tileConfig: Eigenschaften des Kartenteils
             */
            virtual void add(const Node3DConfiguration& tileConfig) = 0;

            /*! \brief Entfernt alle Kartenteile aus dem Spiel und gibt den Speicher frei.
             */
            virtual void unload() = 0;
        };
    }
}

#endif
