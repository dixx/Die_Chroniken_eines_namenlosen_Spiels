/*! \file types.h
 *  \brief Definiert anzeigespezifische Typen.
 *  \note Bestandteil der Leviathan Engine
 */

#ifndef LEVIATHAN_VIDEO_TYPES_H
#define LEVIATHAN_VIDEO_TYPES_H

#include <cstdint>

namespace leviathan {
    namespace video {
        /*! \brief Hilfsobjekt für eine pixelbezogene 2D-Position.
         */
        struct Position2D {
            int32_t x = 0;  //!< X-Koordinate in Pixeln
            int32_t y = 0;  //!< Y-Koordinate in Pixeln
        };
    }
}
#endif
