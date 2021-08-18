/*! \file Dimension2D.h
 *  \brief Hilfsobjekt für Ausdehnungen in Länge und Breite.
 *  \note Bestandteil der Leviathan Engine
 */

#ifndef LEVIATHAN_PUBLIC_INTERFACES_VIDEO_DIMENSION2D_H
#define LEVIATHAN_PUBLIC_INTERFACES_VIDEO_DIMENSION2D_H

#include <cstdint>

namespace leviathan {
    namespace video {

        /*! \brief Hilfsobjekt für Ausdehnungen in Länge und Breite.
         */
        struct Dimension2D {
            uint32_t w = 0;  //!< Breite in Pixeln
            uint32_t h = 0;  //!< Höhe in Pixeln
        };
    }
}
#endif
