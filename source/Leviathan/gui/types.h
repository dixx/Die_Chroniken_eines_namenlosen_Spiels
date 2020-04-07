/*! \file types.h
 *  \brief Definiert GUI-spezifische Typen.
 *  \note Bestandteil der Leviathan Engine
 */

#ifndef LEVIATHAN_GUI_TYPES_H
#define LEVIATHAN_GUI_TYPES_H

#include "../video/types.h"
#include "irrlicht.h"
#include <string>

namespace leviathan {
    namespace gui {

        /*! \brief Definiert das Erscheinungsbild eines Menüs.
         */
        struct MenuConfiguration {
            video::Dimension2D dimension = {0, 0};  //!< Größe des Menüs
            video::Position2D position = {0, 0};  //!< Position relativ zur linken oberen Ecke des Bildschirms
            std::string imageFileName = "";  //!< Name und Pfad der zu verwendenden Bilddatei
            video::Position2D positionOnImage = {0, 0};  //!< Position des Bildausschnitts
            bool hasImageTransparence = false;  //!< Soll Magic Pink im Bild transparent gemacht werden?
        };

        /*! \brief Definiert das Erscheinungsbild eines Buttons.
         */
        struct ButtonConfiguration {
            video::Dimension2D dimension = {0, 0};  //!< Größe des Buttons
            video::Position2D relativePositionInMenu = {0, 0};  //!< Position relativ zur linken oberen Ecke des Menüs
            std::string imageFileName = "";  //!< Name und Pfad der zu verwendenden Bilddatei
            video::Position2D activePositionOnImage = {0, 0};  //!< Position des Bildausschnitts für aktiven Button
            video::Position2D inactivePositionOnImage = {0, 0};  //!< Position des Bildausschnitts für inaktiven Button
            bool hasImageTransparence = false;  //!< Soll Magic Pink im Bild transparent gemacht werden?
        };
    }
}
#endif
