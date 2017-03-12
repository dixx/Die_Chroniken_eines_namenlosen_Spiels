/*! \file Configuration.h
 *  \brief Lesen und Schreiben der Konfig-Datei sowie Verwaltung der enthaltenen Daten.
 *  \note Bestandteil der Leviathan Engine
*/

#ifndef _LEVIATHAN_CONFIGURATION_HEADER
#define _LEVIATHAN_CONFIGURATION_HEADER

#include <irrlicht.h>

namespace leviathan
{
    namespace core
    {

        /*! \class Configuration Configuration.h "Configuration.h"
         *  \brief Enthält Funktionen zum Lesen und Schreiben von Konfig-Dateien sowie zum Verändern von Werten.
         */
        class Configuration
        {

        public:

            /*! \brief Konstruktor.
             *  \param fileSystem: Zeiger auf ein Irrlicht-Dateisystem
             */
            Configuration( irr::io::IFileSystem* fileSystem = 0 );

            /*! \brief Destruktor.
             */
            ~Configuration();

            /*! \brief Liest eine Konfigdatei aus und schreibt die Werte ins System.
             *  \param filename: Logdateiname
             */
            void readFromFile( const irr::io::path& fileName );

            /*! \brief Schreibt die Werte aus dem System in eine Konfigdatei.
             *  \param filename: Logdateiname
             */
            void writeToFile( const irr::io::path& fileName );

            /*! \brief Gibt eine Sammlung von Parametern zur Erstellung eines Irrlicht-Device zurück.
             *  \return Parametersammlung
             */
            const irr::SIrrlichtCreationParameters& getCreationParams() const;

            /*! \brief Gibt die Bildschirm- oder Fensterdimensionen zurück.
             *  \return Höhe und Breite des Fensters/Bildschirms (in Pixel)
             */
            // irr::core::dimension2du getScreenSize() const;

            /*! \brief Gibt die Farbtiefe zurück.
             *  \return Farbtiefe in bit
             */
            // irr::u16 getColorDepht() const;

            /*! \brief Gibt an, ob die Anwendung Vollbild oder im Fenstermodus läuft.
             *  \return `true` wenn Vollbild, ansonsten `false`
             */
            // bool isFullScreen() const;

            /*! \brief Gibt den Render-Modus (Video-Treiber) zurück.
             *  \return Render-Modus
             */
            // irr::video::E_DRIVER_TYPE getRenderMode() const; // TODO check naming!

            /*! \brief Gibt die Sichtweite der Kamera zurück.
             *  \return maximale Sichtweite (in Meter)
             */
            irr::f32 getFarValue() const;

        private:

            irr::io::IFileSystem* fileSystem_; // Zeiger auf das Irrlicht-Dateisystem
            irr::SIrrlichtCreationParameters params_; // Parameter zum Erstellen eines Irrlicht-Device
            irr::f32 farValue_; // Sichtweite der Kamera

            Configuration( const Configuration& ); // Instanz ist nicht kopierbar
            Configuration& operator=( const Configuration& ); // Instanz ist nicht zuweisbar

            // holt einen bestimmten Wert aus dem eingelesenen Inhalt der Konfigdatei.
            const irr::core::stringc getItem(
                    const irr::core::stringc& content,
                    const irr::c8* topic,
                    const irr::c8* itemName,
                    const irr::c8* origin = ""
            );
        };
    }
}

#endif
