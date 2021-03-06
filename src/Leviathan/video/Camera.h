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
            /*! \brief Konstruktor mit Konfiguration.
             *  \param sceneManager: Szenen-Manager des initialisierten Irrlicht Device
             *  \param config: zu verwendende Konfiguration
             */
            Camera(irr::scene::ISceneManager* sceneManager, leviathan::core::Configuration& config);

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
