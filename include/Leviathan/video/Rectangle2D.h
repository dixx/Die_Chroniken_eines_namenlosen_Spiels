/*! \file Rectangle2D.h
 *  \brief Hilfsobjekt für ein 2-dimensionales Rechteck.
 *  \note Bestandteil der Leviathan Engine
 */

#ifndef LEVIATHAN_PUBLIC_INTERFACES_VIDEO_RECTANGLE2D_H
#define LEVIATHAN_PUBLIC_INTERFACES_VIDEO_RECTANGLE2D_H

#include <video/Position2D.h>

namespace leviathan {
    namespace video {

        /*! \brief Hilfsobjekt für ein 2-dimensionales Rechteck.
         */
        struct Rectangle2D {
            Position2D upperLeft = {0, 0};  //!< Koordinaten der oberen linken Ecke, in Pixeln
            Position2D lowerRight = {0, 0};  //!< Koordinaten der unteren rechen Ecke, in Pixeln
        };
    }
}
#endif
