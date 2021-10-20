/*! \file ICamera.h
 *  \brief Bietet Zugriff auf eine Kamera.
 *  \note Bestandteil der Leviathan Engine
 */

#ifndef LEVIATHAN_PUBLIC_INTERFACES_VIDEO_ICAMERA_H
#define LEVIATHAN_PUBLIC_INTERFACES_VIDEO_ICAMERA_H

#include <video/IPositionable.h>

namespace leviathan {
    namespace video {
        struct Vector3D;
        using Position3D = Vector3D;

        /*! \interface ICamera
         *  \brief Bietet Zugriff auf eine Vogelperspektiven-Kamera.
         */
        struct ICamera : IPositionable {
            virtual ~ICamera() {}

            /*! \brief Setzt die Zielposition, auf welche die Kamera gerichtet sein soll.
             *         Wird erst beim nächsten Aufruf von `update` wirksam.
             *  \param targetPosition: Zielposition
             */
            virtual void setTargetPosition(const Position3D& targetPosition) = 0;

            /*! \brief Setzt die Rotationsgeschwindigkeit der Kamera.
             *         Negative Werte lassen die Kamera gegen den Uhrzeigersinn um die Zielposition rotieren.
             *         Wird erst beim nächsten Aufruf von `update` wirksam.
             *  \param rotationSpeed: Rotationsgeschwindigkeit, in °/s
             */
            virtual void setRotationSpeed(const float rotationSpeed) = 0;

            /*! \brief Schaltet die Rotation der Kamera an oder aus.
             *         Wird erst beim nächsten Aufruf von `update` wirksam.
             *  \param isRotating: Kamera rotiert, solange dieser Wert auf `true` gesetzt ist.
             */
            virtual void enableRotation(const bool isRotating) = 0;

            /*! \brief Setzt die Bewegungsgeschwindigkeiten in XYZ-Richtung der Kamera.
             *         Wird erst beim nächsten Aufruf von `update` wirksam.
             *  \param movementSpeed: Bewegungsgeschwindigkeiten in XYZ-Richtung, in Virtuelle Einheiten pro Sekunde
             */
            virtual void setMovementSpeed(const Vector3D& movementSpeed) = 0;

            /*! \brief Schaltet die Bewegung der Kamera an oder aus.
             *         Wird erst beim nächsten Aufruf von `update` wirksam.
             *  \param isMoving: Kamera bewegt sich, solange dieser Wert auf `true` gesetzt ist.
             */
            virtual void enableMovement(const bool isMoving) = 0;

            /*! \brief Positioniert die Kamera, richtet sie aus und rotiert sie bei Bedarf.
             *  \param elapsedSeconds: Dauer des letzten Frames, in Sekunden
             */
            virtual void update(const float elapsedSeconds) = 0;
        };
    }
}

#endif
