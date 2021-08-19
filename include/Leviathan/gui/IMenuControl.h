/*! \file IMenuControl.h
 *  \brief Erstellen und Verwalten von Menüs.
 *  \note Bestandteil der Leviathan Engine.
 */

#ifndef LEVIATHAN_PUBLIC_INTERFACES_GUI_IMENUCONTROL_H
#define LEVIATHAN_PUBLIC_INTERFACES_GUI_IMENUCONTROL_H

#include <string>
#include <video/Dimension2D.h>
#include <video/Position2D.h>

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

        /*! \interface IMenuControl
         *  \brief Bietet Zugriff auf Funktionen zum Erstellen und Verwalten von Menüs.
         */
        struct IMenuControl {
            virtual ~IMenuControl() {}

            /*! \brief Fügt ein neues Menü hinzu.
             *  \param name: Bezeichner/Identifikator für das neue Menü
             *  \param config: Definition des Erscheinungsbildes des neuen Menüs
             */
            virtual void addMenu(const wchar_t* name, const MenuConfiguration& config) = 0;

            /*! \brief Fügt einem Menü einen neuen Button hinzu.
             *  \param menuName: Bezeichner/Identifikator für das Menü
             *  \param buttonName: Bezeichner/Identifikator für den neuen Button
             *  \param config: Definition des Erscheinungsbildes des neuen Buttons
             */
            virtual void addButton(
                const wchar_t* menuName, const wchar_t* buttonName, const ButtonConfiguration& config) = 0;

            /*! \brief Macht das Menü sichtbar für Anzeige und Interaktionen.
             *  \param name: Bezeichner/Identifikator für das neue Menü
             */
            virtual void enable(const wchar_t* name) = 0;

            /*! \brief Macht das Menü unsichtbar für Anzeige und Interaktionen.
             *  \param name: Bezeichner/Identifikator für das neue Menü
             */
            virtual void disable(const wchar_t* name) = 0;

            /*! \brief Zeichnet alle aktiven Menüs auf den Bildschirm.
             */
            virtual void draw() = 0;
        };
    }
}
#endif
