/*! \file Ground.h
 *  \brief Bietet Zugriff auf begehbaren Boden.
 *  \note Bestandteil der Leviathan Engine
 */

#ifndef LEVIATHAN_WORLD_GROUND_H
#define LEVIATHAN_WORLD_GROUND_H

#include <world/Node3DConfiguration.h>

namespace leviathan {
    namespace world {
        class NodeManager;

        /*! \class Ground
         *  \brief Bietet Zugriff auf begehbaren Boden
         */
        class Ground {
        public:
            /*! \brief Konstruktor mit Konfiguration.
             *  \param nodeManager: Instanz der 3D-Szenenknoten-Verwaltung
             */
            explicit Ground(NodeManager& nodeManager);

            /*! \brief Destruktor.
             */
            ~Ground();

            Ground() = delete;
            Ground(const Ground&) = delete;
            Ground(const Ground&&) = delete;
            Ground& operator=(const Ground&) = delete;
            Ground& operator=(const Ground&&) = delete;

            /*! \brief Fügt ein Kartenteil hinzu.
             *  \param tileConfig: Eigenschaften des Kartenteils
             */
            void add(const Node3DConfiguration& tileConfig);

            /*! \brief Entfernt alle Kartenteile aus dem Spiel und gibt den Speicher frei.
             */
            void unload();

        private:
            NodeManager& nodeManager_;
        };
    }
}

#endif
