/*! \file IDecorations.h
 *  \brief Bietet Zugriff auf rein dekorative Elemente.
 *  \note Bestandteil der Leviathan Engine
 */

#ifndef LEVIATHAN_PUBLIC_INTERFACES_WORLD_IDECORATIONS_H
#define LEVIATHAN_PUBLIC_INTERFACES_WORLD_IDECORATIONS_H

#include <video/IPositionable.h>

namespace leviathan {
    namespace world {
        struct Node3DConfiguration;

        /*! \interface IDecorations
         *  \brief Bietet Zugriff auf rein dekorative Elemente
         */
        struct IDecorations {
            virtual ~IDecorations() {}

            /*! \brief Fügt ein dekoratives Element hinzu.
             *  \param tileConfig: Eigenschaften des dekorativen Elements
             */
            virtual void add(const Node3DConfiguration& tileConfig) = 0;

            /*! \brief Entfernt alle dekorativen Elemente aus dem Spiel und gibt den Speicher frei.
             */
            virtual void unload() = 0;
        };
    }
}

#endif
