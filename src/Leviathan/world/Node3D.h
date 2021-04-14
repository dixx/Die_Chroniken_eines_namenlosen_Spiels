/*! \file Node3D.h
 *  \brief Ein 3D-Objekt.
 *  \note Bestandteil der Leviathan Engine
 */

#ifndef LEVIATHAN_WORLD_NODE3D_H
#define LEVIATHAN_WORLD_NODE3D_H

#include <video/Vector3D.h>
#include <world/INode3D.h>

namespace leviathan {
    namespace world {

        /*! \class Node3D
         *  \brief Ein 3D-Objekt.
         */
        class Node3D : public INode3D {
        public:
            Node3D() {}
            ~Node3D() {}
            virtual void setDesiredPostition(const video::Position3D& targetPosition) override;
        };
    }
}
#endif
