/*! \file Configuration.h
 *  \brief Lesen und Schreiben der Konfig-Datei sowie Verwaltung der enthaltenen Daten.
 *  \note Bestandteil der Leviathan Engine
*/

#ifndef _LEVIATHAN_CONFIGURATION_HEADER
#define _LEVIATHAN_CONFIGURATION_HEADER

#include <irrlicht.h>
#include <cstdint>
#include <string>
#include "Logger.h"
#include "MapWithDefault.h"

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
             *  \note ein Default-Objekt wird erstellt
             */
            Configuration();

            /*! \brief Destruktor.
             */
            ~Configuration();

            Configuration( const Configuration& ) = delete;
            Configuration& operator=( const Configuration& ) = delete;

            /*! \brief Liest eine Konfigdatei aus und schreibt die Werte ins System.
             *  \param filename: Konfigdateiname
             *  \param fileSystem: Zeiger auf ein Irrlicht-Dateisystem
             */
            void readFromFile( const irr::io::path& fileName, irr::io::IFileSystem* fileSystem = nullptr );

            /*! \brief Schreibt die Werte aus dem System in eine Konfigdatei.
             *  \param filename: Konfigdateiname
             *  \param fileSystem: Zeiger auf ein Irrlicht-Dateisystem
             */
            // void writeToFile( const irr::io::path& fileName, irr::io::IFileSystem* fileSystem = 0 );

            /*! \brief Gibt eine Sammlung von Parametern zur Erstellung eines Irrlicht-Device zurück.
             *  \return Parametersammlung
             */
            const irr::SIrrlichtCreationParameters& getGraphicEngineParams() const;

            /*! \brief Gibt die Sichtweite der Kamera zurück.
             *  \return maximale Sichtweite (in Meter)
             */
            float getFarValue() const;

            /*! \brief Gibt den Loglevel zurück.
             *  \return Loglevel
             */
            Logger::Level getLoggingLevel() const;

            /*! \brief Gibt die Anzahl der maximal anzuzeigenden Bilder pro Sekunde zurück.
             *  \return Anzahl der maximal anzuzeigenden Bilder pro Sekunde
             */
            uint32_t getMaxFPS() const;

            /*! \brief Gibt anhand einer Sektion und eines Schlüssels einen Integer-Wert zurück.
             *  \note Nur für Testzwecke gedacht, Benutzen auf eigene Gefahr.
             *  \param section: Name der Sektion
             *  \param key: Name des Schlüssels
             *  \return Integer-Wert
             */
            int getInt( const irr::core::stringc& section, const irr::core::stringc& key );

        private:

            irr::core::list<irr::core::stringc> content_;
            irr::SIrrlichtCreationParameters params_; // Parameter zum Erstellen eines Irrlicht-Device
            float farValue_; // Sichtweite der Kamera
            Logger::Level loggingLevel_;
            uint32_t maxFPS_;
            MapWithDefault<std::string, irr::video::E_DRIVER_TYPE> driverMap {
                {"SOFTWARE", irr::video::EDT_SOFTWARE},
                {"NULL", irr::video::EDT_NULL},
                {"BURNINGSVIDEO", irr::video::EDT_BURNINGSVIDEO},
                {"OPENGL", irr::video::EDT_OPENGL},
                {"DIRECT3D8", irr::video::EDT_DIRECT3D8},
                {"DIRECT3D9", irr::video::EDT_DIRECT3D9}
            };
            MapWithDefault<std::string, Logger::Level> logLevelMap {
                {"INFO", Logger::Level::INFO},
                {"ALL", Logger::Level::ALL},
                {"DEBUG", Logger::Level::DEBUG},
                {"DETAIL", Logger::Level::DETAIL}
            };

            void generateContent( const irr::io::path& fileName, irr::io::IFileSystem* fileSystem );
            const irr::core::stringc getItem(
                const irr::core::stringc& section,
                const irr::core::stringc& key,
                const irr::core::stringc& defaultValue = ""
            );
        };
    }
}

#endif
