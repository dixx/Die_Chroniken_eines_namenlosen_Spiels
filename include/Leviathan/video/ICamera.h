/*! \file ICamera.h
 *  \brief Bietet Zugriff auf eine Kamera.
 *  \note Bestandteil der Leviathan Engine
 */

#ifndef LEVIATHAN_PUBLIC_INTERFACES_VIDEO_ICAMERA_H
#define LEVIATHAN_PUBLIC_INTERFACES_VIDEO_ICAMERA_H

namespace leviathan {
    namespace video {
        struct Vector3D;
        using Position3D = Vector3D;

        /*! \interface ICamera
         *  \brief Bietet Zugriff auf eine Kamera.
         */
        struct ICamera {
            virtual ~ICamera() {}

            /*! \brief Setzt die Zielposition, auf welche sich die Kamera ausrichten soll
             *  \param targetPosition: Zielposition
             */
            virtual void setTargetPosition(const Position3D& targetPosition) = 0;

            /*! \brief Setzt das Positionsoffset relativ zur Zielposition
             *  \param offset: Positionsoffset relativ zur Zielposition
             */
            virtual void setOffset(const Position3D& offset) = 0;

            /*! \brief Positioniert die Kamera und richtet sie aus.
             */
            virtual void update() = 0;
        };
    }
}

#endif
