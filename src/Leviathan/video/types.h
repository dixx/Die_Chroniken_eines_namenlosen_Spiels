/*! \file types.h
 *  \brief Definiert anzeigespezifische Typen.
 *  \note Bestandteil der Leviathan Engine
 */

#ifndef LEVIATHAN_VIDEO_TYPES_H
#define LEVIATHAN_VIDEO_TYPES_H

#include <cstdint>
#include <irrlicht.h>
#include <video/Vector3D.h>

namespace leviathan {
    namespace video {

        /*! \brief Hilfsobjekt für Ausdehnungen in Länge und Breite.
         */
        struct Dimension2D {
            uint32_t w = 0;  //!< Breite in Pixeln
            uint32_t h = 0;  //!< Höhe in Pixeln
        };

        /*! \brief Hilfsobjekt für eine pixelbezogene 2D-Position.
         */
        struct Position2D {
            int32_t x = 0;  //!< X-Koordinate in Pixeln
            int32_t y = 0;  //!< Y-Koordinate in Pixeln
        };

        /*! \brief Hilfsobjekt für generische 3D-Vektoren, kann sich in Irrlicht-Vektor konvertieren.
         */
        struct Vector3DCompatible : Vector3D {
            irr::core::vector3df toIrrlichtVector() const {
                return irr::core::vector3df(x, y, z);
            }
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
