/*! \file Vector3DCompatible.h
 *  \brief Hilfsobjekt für generische 3D-Vektoren, kann sich in Irrlicht-Vektor konvertieren.
 *  \note Bestandteil der Leviathan Engine
 */

#ifndef LEVIATHAN_VIDEO_VECTOR3D_COMPATIBLE_H
#define LEVIATHAN_VIDEO_VECTOR3D_COMPATIBLE_H

#include "vector3d.h"
#include <initializer_list>
#include <video/Vector3D.h>

namespace leviathan {
    namespace video {
        /*! \brief Hilfsobjekt für generische 3D-Vektoren, kann sich in Irrlicht-Vektor konvertieren.
         */
        struct Vector3DCompatible : Vector3D {
            Vector3DCompatible();
            Vector3DCompatible(std::initializer_list<float> list);
            Vector3DCompatible(const Vector3DCompatible& other);
            Vector3DCompatible(const Vector3DCompatible&& other);
            Vector3DCompatible(const Vector3D& other);
            Vector3DCompatible(const Vector3D&& other);
            Vector3DCompatible(const irr::core::vector3df& other);
            Vector3DCompatible(const irr::core::vector3df&& other);
            Vector3DCompatible& operator=(const Vector3D& other);

            irr::core::vector3df toIrrlichtVector() const;
        };

        /*! \brief Alias für Skalierung der Ausdehnungen in Länge, Breite und Tiefe.
         */
        using Scale3DCompatible = Vector3DCompatible;

        /*! \brief Alias für eine 3D-Position.
         */
        using Position3DCompatible = Vector3DCompatible;

        /*! \brief Alias für Rotation in einem kartesischen 3D-Koordinatensystem, in Grad.
         */
        using Rotation3DCompatible = Vector3DCompatible;
    }
}
#endif
