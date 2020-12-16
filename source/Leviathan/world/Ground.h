/*! \file Ground.h
 *  \brief Bietet Zugriff auf begehbaren Boden.
 *  \note Bestandteil der Leviathan Engine
 */

#ifndef LEVIATHAN_WORLD_GROUND_H
#define LEVIATHAN_WORLD_GROUND_H

#include "irrlicht.h"

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
            Ground(irr::scene::ISceneManager* sceneManager);

            ~Ground() = default;
            Ground() = delete;
            Ground(const Ground&) = delete;
            Ground& operator=(const Ground&) = delete;

        private:
            irr::scene::ISceneManager* sceneManager_ = nullptr;
        };
    }
}

#endif
