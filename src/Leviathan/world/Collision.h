/*! \file Collision.h
 *  \brief Definition einer Kollision.
 *  \note Bestandteil der Leviathan Engine
 *        Wird nur intern benutzt.
 */

#ifndef LEVIATHAN_WORLD_COLLISION_H
#define LEVIATHAN_WORLD_COLLISION_H

#include <video/Vector3D.h>

namespace leviathan {
    namespace world {

        /*! \brief Definition einer Kollision.
         */
        struct Collision {
            video::Position3D collisionPoint = {0.f, 0.f, 0.f};
            bool happened = false;
        };
    }
}
#endif
