/*! \file Vector3D.h
 *  \brief Generischer 3D-Vektor.
 *  \note Bestandteil der Leviathan Engine
 */

#ifndef LEVIATHAN_PUBLIC_INTERFACES_VIDEO_VECTOR3D_H
#define LEVIATHAN_PUBLIC_INTERFACES_VIDEO_VECTOR3D_H

#include <cfloat>

namespace leviathan {
    namespace video {
        struct Vector3D;

        /*! \brief Alias für eine 3D-Position.
         */
        using Position3D = Vector3D;

        /*! \brief Alias für Rotationsinformationen in 3 Achsen, Angaben in °.
         */
        using Rotation3D = Vector3D;

        /*! \brief Alias für Skalierung von 3 Dimensionen, Angaben als Multiplikatoren.
         */
        using Scale3D = Vector3D;

        /*! \brief Generischer 3D-Vektor.
         */
        struct Vector3D {
            float x = 0;
            float y = 0;
            float z = 0;

            /*! \brief Vergleicht die drei Dimensionen dieses Vektors mit denen eines anderen Vektors.
             *  \param other: anderer Vektor
             *  \param tolerance: Unterschiede innerhalb dieser Toleranz gelten als Gleich.
             */
            bool equals(const Vector3D& other, float tolerance = FLT_EPSILON) const;

            /*! \brief Setzt die Länge des Vektors, die Richtung bleibt dabei erhalten.
             *  \param length: gewünschte Länge
             */
            void setLength(float length);

            /*! \brief Get the rotations that would make a (0,0,1) direction vector point in the same direction as this
             * direction vector.
             */
            Rotation3D getHorizontalAngle() const;
        };

        Vector3D operator+(Vector3D const& lhs, Vector3D const& rhs);
        Vector3D operator-(Vector3D const& lhs, Vector3D const& rhs);
    }
}
#endif
