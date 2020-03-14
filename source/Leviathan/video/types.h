/*! \file types.h
 *  \brief Definiert anzeigespezifische Typen.
 *  \note Bestandteil der Leviathan Engine
 */

#ifndef LEVIATHAN_VIDEO_TYPES_H
#define LEVIATHAN_VIDEO_TYPES_H

#include <cstdint>

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
    }
}
#endif
