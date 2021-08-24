/*! \file IConfiguration.h
 *  \brief Lesen und Schreiben der Konfig-Datei sowie Verwaltung der enthaltenen Daten.
 *  \note Bestandteil der Leviathan Engine
 */

#ifndef LEVIATHAN_PUBLIC_INTERFACES_CORE_ICONFIGURATION_H
#define LEVIATHAN_PUBLIC_INTERFACES_CORE_ICONFIGURATION_H

namespace leviathan {
    namespace video {
        struct Dimension2D;
    }

    namespace core {

        /*! \interface IConfiguration
         *  \brief Enthält Funktionen zum Lesen und Schreiben von Konfig-Dateien sowie zum Verändern von Werten.
         */
        struct IConfiguration {
            virtual ~IConfiguration() {}

            /*! \brief Gibt die Größe des anzuzeigenden Fensters in Pixel zurück.
             *  \return Größe des anzuzeigenden Fensters in Pixel
             */
            virtual const video::Dimension2D& getScreenSize() const = 0;
        };
    }
}

#endif
