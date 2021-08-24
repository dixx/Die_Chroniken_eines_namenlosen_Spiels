/*! \file MousePointerConfiguration.h
 *  \brief Konfiguration für einen Mauszeiger.
 *  \note Bestandteil der Leviathan Engine
 */

#ifndef LEVIATHAN_PUBLIC_INTERFACES_GUI_MOUSEPOINTERCONFIGURATION_H
#define LEVIATHAN_PUBLIC_INTERFACES_GUI_MOUSEPOINTERCONFIGURATION_H

#include <string>
#include <video/Position2D.h>
#include <video/Rectangle2D.h>

namespace leviathan {
    namespace gui {
        /*! \brief Konfiguration für einen Mauszeiger.
         */
        struct MousePointerConfiguration {
            std::string imageFileName = "";  //!< Dateiname (mit Pfad) des Ausgangsbildes
            video::Rectangle2D imageArea = {{0, 0}, {0, 0}};  //!< zu verwendender Bildausschnitt
            video::Position2D hotSpot = {
                0, 0};  //!< Punkt innerhalb des resultierenden Bildausschnittes, der als "Mauszeiger-Spitze" dient
        };
    }
}
#endif
