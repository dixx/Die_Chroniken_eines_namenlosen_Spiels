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
            Camera(irr::scene::ISceneManager* sceneManager, core::Configuration& config);

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
            irr::scene::ICameraSceneNode* mCamera = nullptr;
            video::Position3DCompatible mTargetPosition = video::Position3DCompatible({});
            video::Vector3DCompatible mOffset = video::Vector3DCompatible({0.f, 15.f, -3.f});
            float mRotation = 0.f;
            float mRotationSpeed = 0.f;
            bool mIsRotating = false;
            video::Vector3DCompatible mMovementSpeed = video::Vector3DCompatible({});
            bool mIsMoving = false;
        };
    }
}

#endif
