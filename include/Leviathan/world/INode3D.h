/*! \file INode3D.h
 *  \brief Interface für ein 3D-Objekt.
 *  \note Bestandteil der Leviathan Engine
 */

#ifndef LEVIATHAN_PUBLIC_INTERFACES_WORLD_INODE3D_H
#define LEVIATHAN_PUBLIC_INTERFACES_WORLD_INODE3D_H

#include <video/Vector3D.h>

namespace leviathan {
    namespace world {
        /*! \interface INode3D
         *  \brief Interface für ein 3D-Objekt.
         */
        struct INode3D {
            virtual ~INode3D() {}

            /*! \brief Setzt die gewünschte neue Position.
             *  \note Wenn die Kollisionserkennung für dieses Objekt aktiviert ist, wird die tatsächliche neue Position
             *        möglicherweise eine Korrektur gegenüber der gewünschten Position erfahren haben.
             *  \param targetPosition: gewünschte neue Position
             */
            virtual void setDesiredPostition(const video::Position3D& targetPosition) = 0;
        };
    }
}
#endif
