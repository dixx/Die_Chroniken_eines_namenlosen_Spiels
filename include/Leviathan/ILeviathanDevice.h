/*! \file ILeviathanDevice.h
 *  \brief Die eigentliche 'Leviathan Engine'.
 *         Bietet Zugriff auf alle Funktionalitäten, kümmert sich um Instanzierung ihrer Teile usw.
 *  \note Bestandteil der Leviathan Engine
 */

#ifndef LEVIATHAN_PUBLIC_INTERFACES_LEVIATHANDEVICE_H
#define LEVIATHAN_PUBLIC_INTERFACES_LEVIATHANDEVICE_H

#include <characters/IHeroes.h>
#include <core/IConfiguration.h>
#include <core/IGameStateManager.h>
#include <gui/IMenuControl.h>
#include <gui/IMousePointerControl.h>
#include <input/IActions.h>
#include <world/IGround.h>

namespace leviathan {

    /*! \interface ILeviathanDevice
     *  \brief Die eigentliche Engine.
     */
    struct ILeviathanDevice {
        virtual ~ILeviathanDevice() {}

        /*! \brief Der eigentliche Game-Loop.
         *         Diese Methode kümmert sich um das Aktualisieren und Zeichnen des aktuellen Spielzustandes,
         *         Berechnen der Zeit, Entscheiden ob die KI aktualisiert werden muss usw.
         */
        virtual void run() = 0;

        /*! /brief Stoppt den Game-Loop und fährt die Engine herunter.
         *  /note Der aktuelle Game-Loop-Durchlauf läuft noch zu Ende durch.
         */
        virtual void halt() = 0;

        /*! \brief Zugriff auf die Helden.
         */
        virtual characters::IHeroes& Heroes() = 0;

        /*! \brief Zugriff auf die aktuelle Konfiguration.
         */
        virtual core::IConfiguration& Configuration() = 0;

        /*! \brief Zugriff auf die Verwaltung der Spielzustände.
         */
        virtual core::IGameStateManager& GameStateManager() = 0;

        /*! \brief Zugriff auf Erstellen und Verwalten von Menüs.
         */
        virtual gui::IMenuControl& MenuControl() = 0;

        /*! \brief Zugriff auf Mauszeiger.
         */
        virtual gui::IMousePointerControl& MousePointerControl() = 0;

        /*! \brief Zugriff auf Input-Mappings.
         */
        virtual input::IActions& Actions() = 0;

        /*! \brief Zugriff auf begehbaren Boden.
         */
        virtual world::IGround& Ground() = 0;
    };
}

#endif
