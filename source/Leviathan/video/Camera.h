/*! \file Camera.h
 *  \brief Bietet Zugriff auf eine Verfolgerkamera.
 *  \note Bestandteil der Leviathan Engine
 */

#ifndef LEVIATHAN_VIDEO_CAMERA_H
#define LEVIATHAN_VIDEO_CAMERA_H

#include "../core/Configuration.h"
#include "irrlicht.h"

namespace leviathan {
    namespace video {

        /*! \class Camera
         *  \brief Bietet Zugriff auf eine Verfolgerkamera
         */
        class Camera {
        public:
            /*! \brief Konstruktor.
             *  \param graphicDevice: initialisiertes Irrlicht Device
             */
            explicit Camera(irr::IrrlichtDevice* graphicDevice);

            /*! \brief Konstruktor mit Konfiguration.
             *  \param graphicDevice: initialisiertes Irrlicht Device
             *  \param config: zu verwendende Konfiguration
             */
            Camera(irr::IrrlichtDevice* graphicDevice, leviathan::core::Configuration& config);

            ~Camera() = default;
            Camera() = delete;
            Camera(const Camera&) = delete;
            Camera& operator=(const Camera&) = delete;

        private:
            irr::scene::ICameraSceneNode* camera_ = nullptr;
        };
    }
}

#endif
