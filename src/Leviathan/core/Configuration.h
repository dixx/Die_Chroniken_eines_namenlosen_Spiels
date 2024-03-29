/*! \file Configuration.h
 *  \brief Lesen und Schreiben der Konfig-Datei sowie Verwaltung der enthaltenen Daten.
 *  \note Bestandteil der Leviathan Engine
 */

#ifndef LEVIATHAN_CORE_CONFIGURATION_H
#define LEVIATHAN_CORE_CONFIGURATION_H

#include "../support/MapWithDefault.h"
#include "EDriverTypes.h"
#include "SIrrCreationParameters.h"
#include "yaml-cpp/yaml.h"
#include <core/IConfiguration.h>
#include <core/ILogger.h>
#include <cstdint>
#include <string>
#include <video/Dimension2D.h>

namespace leviathan {
    namespace core {

        /*! \class Configuration Configuration.h "Configuration.h"
         *  \brief Enthält Funktionen zum Lesen und Schreiben von Konfig-Dateien sowie zum Verändern von Werten.
         */
        class Configuration final : public IConfiguration {
        public:
            /*! \brief Konstruktor mit Konfigurationsdatei.
             *  \param filename: Konfigdateiname
             */
            explicit Configuration(const char* fileName);

            /*! \brief Destruktor.
             */
            ~Configuration() = default;

            Configuration() = delete;
            Configuration(const Configuration&) = delete;
            Configuration(const Configuration&&) = delete;
            Configuration& operator=(const Configuration&) = delete;
            Configuration& operator=(const Configuration&&) = delete;

            /*! \brief Liest eine Konfigdatei aus und schreibt die Werte ins System.
             *  \param filename: Konfigdateiname
             */
            void loadFromFile(const char* fileName);

            /*! \brief Schreibt die Werte aus dem System in eine Konfigdatei.
             *  \param filename: Konfigdateiname
             */
            // void writeToFile(const irr::io::path& fileName);

            /*! \brief Gibt eine Sammlung von Parametern zur Erstellung eines Irrlicht-Device zurück.
             *  \return Parametersammlung
             */
            const irr::SIrrlichtCreationParameters& getGraphicEngineParams() const;

            /*! \brief Gibt die Sichtweite der Kamera zurück.
             *  \return maximale Sichtweite (in Meter)
             */
            const float& getFarValue() const;

            /*! \brief Gibt den Loglevel zurück.
             *  \return Loglevel
             */
            const ILogger::Level& getLoggingLevel() const;

            /*! \brief Gibt die Anzahl der maximal anzuzeigenden Bilder pro Sekunde zurück.
             *  \return Anzahl der maximal anzuzeigenden Bilder pro Sekunde
             */
            const uint32_t& getMaxFPS() const;

            /*! \brief Gibt die Größe des anzuzeigenden Fensters in Pixel zurück.
             *  \return Größe des anzuzeigenden Fensters in Pixel
             */
            const video::Dimension2D& getScreenSize() const override;

        private:
            irr::SIrrlichtCreationParameters mParams = irr::SIrrlichtCreationParameters();
            float mFarValue = 300.0f;  // Sichtweite der Kamera
            ILogger::Level mLoggingLevel = ILogger::Level::INFO;
            uint32_t mMaxFPS = 60;
            video::Dimension2D mScreenSize = {800, 600};
            MapWithDefault<std::string, irr::video::E_DRIVER_TYPE> mDriverMap {{"OPENGL", irr::video::EDT_OPENGL},
                {"DIRECT3D9", irr::video::EDT_DIRECT3D9}, {"DIRECT3D8", irr::video::EDT_DIRECT3D8},
                {"SOFTWARE", irr::video::EDT_SOFTWARE}, {"BURNINGSVIDEO", irr::video::EDT_BURNINGSVIDEO},
                {"NULL", irr::video::EDT_NULL}};
            MapWithDefault<std::string, ILogger::Level> mLogLevelMap {{"INFO", ILogger::Level::INFO},
                {"ALL", ILogger::Level::ALL}, {"DEBUG", ILogger::Level::DEBUG}, {"DETAIL", ILogger::Level::DETAIL}};

            void setCameraValues(YAML::Node& content);
            void setGeneralValues(YAML::Node& content);
            void setVideoValues(YAML::Node& content);
            void setCameraDefaults();
            void setGeneralDefaults();
            void setVideoDefaults();
        };
    }
}

#endif
