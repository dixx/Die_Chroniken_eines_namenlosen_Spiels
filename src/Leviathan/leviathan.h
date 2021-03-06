/*! \file leviathan.h
 *  \brief Interface der 'Leviathan Engine'.
 *         Dies ist der einzige Header der inkludiert werden muss.
 */

#ifndef LEVIATHAN_H
#define LEVIATHAN_H

#include "LeviathanDevice.h"

//! Alle bedienbaren Teile der Leviathan Game Engine findest du hier.
namespace leviathan {

    //! Grundlegende Bestandteile der Engine.
    namespace core {}

    //! Hilfsklassen für Grafische Benutzeroberflächen
    namespace gui {}

    //! Hilfsklassen für Eingabegeräte
    namespace input {}

    //! Hilfsklassen für das Anzeigen
    namespace video {}

    //! Hilfsklassen für die Spielwelt
    namespace world {}
}

#endif
