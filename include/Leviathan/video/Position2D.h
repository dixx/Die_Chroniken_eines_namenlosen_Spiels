/*! \file Position2D.h
 *  \brief Hilfsobjekt für eine pixelbezogene 2D-Position.
 *  \note Bestandteil der Leviathan Engine
 */

#ifndef LEVIATHAN_PUBLIC_INTERFACES_VIDEO_POSITION2D_H
#define LEVIATHAN_PUBLIC_INTERFACES_VIDEO_POSITION2D_H

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
