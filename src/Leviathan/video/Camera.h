/*! \file Camera.h
 *  \brief Bietet Zugriff auf eine Verfolgerkamera.
 *  \note Bestandteil der Leviathan Engine
 */

#ifndef LEVIATHAN_VIDEO_CAMERA_H
#define LEVIATHAN_VIDEO_CAMERA_H

#include "Vector3DCompatible.h"
#include "vector3d.h"
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
            Camera(const Camera&&) = delete;
            Camera& operator=(const Camera&) = delete;
            Camera& operator=(const Camera&&) = delete;

            void setTargetPosition(const Position3D& targetPosition) override;

            void setRotationSpeed(const float rotationSpeed) override;

            void enableRotation(const bool isRotating) override;

            void setMovementSpeed(const Vector3D& movementSpeed) override;

            void enableMovement(const bool isMoving) override;

            void update(const float elapsedSeconds) override;

            Position3D getPosition() const override;

            void setPosition(const Position3D& position) override;

        private:
            irr::scene::ICameraSceneNode* camera_ = nullptr;
            irr::core::vector3df targetPosition_ = irr::core::vector3df();
            irr::core::vector3df offset_ = irr::core::vector3df(0.f, 15.f, -3.f);
            float rotation_ = 0.f;
            float rotationSpeed_ = 0.f;
            bool isRotating_ = false;
            irr::core::vector3df movementSpeed_ = irr::core::vector3df();
            bool isMoving_ = false;
        };
    }
}

#endif
