/*! \file Ground.h
 *  \brief Bietet Zugriff auf begehbaren Boden.
 *  \note Bestandteil der Leviathan Engine
 */

#ifndef LEVIATHAN_WORLD_GROUND_H
#define LEVIATHAN_WORLD_GROUND_H

#include "irrlicht.h"
#include "types.h"

namespace leviathan {
    namespace world {

        /*! \class Ground
         *  \brief Bietet Zugriff auf begehbaren Boden
         */
        class Ground {
        public:
            /*! \brief Konstruktor mit Konfiguration.
             *  \param sceneManager: Szenen-Manager des initialisierten Irrlicht Device
             */
            explicit Ground(irr::scene::ISceneManager* sceneManager);

            /*! \brief Destruktor.
             */
            ~Ground();

            Ground() = delete;
            Ground(const Ground&) = delete;
            Ground& operator=(const Ground&) = delete;

            /*! \brief Fügt ein Kartenteil hinzu.
             *  \param tileConfig: Eigenschaften des Kartenteils
             */
            void add(const GroundTileConfiguration& tileConfig);

            /*! \brief Entfernt alle Kartenteile aus dem Spiel und gibt den Speicher frei.
             */
            void unload();

        private:
            irr::scene::ISceneManager* sceneManager_ = nullptr;
            irr::scene::IMeshSceneNode* groundTile_ = nullptr;

            void transformMesh(irr::scene::IMesh* mesh, const GroundTileConfiguration& tileConfig);
        };
    }
}

#endif
