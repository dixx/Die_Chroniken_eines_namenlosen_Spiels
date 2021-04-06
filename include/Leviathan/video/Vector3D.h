/*! \file Vector3D.h
 *  \brief Generischer 3D-Vektor.
 *  \note Bestandteil der Leviathan Engine
 */

#ifndef LEVIATHAN_PUBLIC_INTERFACES_VIDEO_VECTOR3D_H
#define LEVIATHAN_PUBLIC_INTERFACES_VIDEO_VECTOR3D_H

namespace leviathan {
    namespace video {
        /*! \brief Generischer 3D-Vektor.
         */
        struct Vector3D {
            float x = 0;
            float y = 0;
            float z = 0;
        };

        /*! \brief Alias für eine 3D-Position.
         */
        using Position3D = Vector3D;
    }
}
#endif
