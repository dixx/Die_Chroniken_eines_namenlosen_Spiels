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

        inline Vector3D operator+(Vector3D const& lhs, Vector3D const& rhs) {
            return {lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z};
        }

        inline Vector3D operator-(Vector3D const& lhs, Vector3D const& rhs) {
            return {lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z};
        }

        /*! \brief Alias für eine 3D-Position.
         */
        using Position3D = Vector3D;

        /*! \brief Alias für Rotationsinformationen in 3 Achsen, Angaben in °.
         */
        using Rotation3D = Vector3D;

        /*! \brief Alias für Skalierung von 3 Dimensionen, Angaben als Multiplikatoren.
         */
        using Scale3D = Vector3D;
    }
}
#endif
