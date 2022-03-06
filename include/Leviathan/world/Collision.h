/*! \file Collision.h
 *  \brief Definition einer Kollision.
 *  \note Bestandteil der Leviathan Engine
 */

#ifndef LEVIATHAN_PUBLIC_INTERFACES_WORLD_COLLISION_H
#define LEVIATHAN_PUBLIC_INTERFACES_WORLD_COLLISION_H

#include <video/Vector3D.h>

namespace leviathan {
    namespace world {

        /*! \struct Collision
         *  \brief Definition einer Kollision.
         */
        struct Collision {
            //! Der exakte Punkt der Kollision.
            video::Position3D collisionPoint = {0.f, 0.f, 0.f};

            //! Gibt an, ob eine Kollision stattgefunden hat.
            bool happened = false;
        };
    }
}
#endif
