/*! \file Camera.h
 *  \brief Bietet Zugriff auf eine Verfolgerkamera.
 *  \note Bestandteil der Leviathan Engine
 */

#ifndef LEVIATHAN_VIDEO_CAMERA_H
#define LEVIATHAN_VIDEO_CAMERA_H

#include "Vector3DCompatible.h"
#include <video/ICamera.h>

namespace irr {
    namespace scene {
        class ICameraSceneNode;
        class ISceneManager;
    }
}

namespace leviathan {
    namespace core {
        class Configuration;
    }

    namespace video {

        /*! \class Camera
         *  \brief Bietet Zugriff auf eine Verfolgerkamera
         */
        class Camera final : public ICamera {
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

            void setTargetPosition(const Position3D& targetPosition) override;

            void setOffset(const Vector3D& offset) override;

            void update() override;

        private:
            irr::scene::ICameraSceneNode* camera_ = nullptr;
            Vector3DCompatible targetPosition_ = Vector3DCompatible({});
            Vector3DCompatible offset_ = Vector3DCompatible({-3.f, 15.f, -3.f});
        };
    }
}

#endif
