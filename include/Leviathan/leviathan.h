/*! \file leviathan.h
 *  \brief Interface der 'Leviathan Engine'.
 *         Dies ist der einzige Header der inkludiert werden muss.
 */

#ifndef LEVIATHAN_PUBLIC_INTERFACES_LEVIATHAN_H
#define LEVIATHAN_PUBLIC_INTERFACES_LEVIATHAN_H

#include <ILeviathanDevice.h>

//! Alle bedienbaren Teile der Leviathan Game Engine findest du hier.
namespace leviathan {

    //! Hilfsklassen für Helden und NPCs
    namespace characters {}

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

    /*! \brief Lädt die Konfiguration aus der angegebenen Datei und initialisiert alle Bestandteile
     *         der Engine.
     *  \param configFileName: Konfigdateiname
     */
    ILeviathanDevice& createDevice(const char* configFileName);
}

#endif
