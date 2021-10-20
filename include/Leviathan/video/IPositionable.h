/*! \file IPositionable.h
 *  \brief Interface zum Positionieren. Wird von der Kollisionserkennung verwendet.
 *  \note Bestandteil der Leviathan Engine
 */

#ifndef LEVIATHAN_PUBLIC_INTERFACES_VIDEO_IPOSITIONABLE_H
#define LEVIATHAN_PUBLIC_INTERFACES_VIDEO_IPOSITIONABLE_H

namespace leviathan {
    namespace video {
        struct Vector3D;
        using Position3D = Vector3D;

        /*! \interface IPositionable
         *  \brief Bietet Zugriff auf die Position eines Objekts.
         *  \note Wird von der Kollisionserkennung verwendet, um die Position eines Objekts nach einer Kollision
         *        automatisch anzupassen.
         */
        struct IPositionable {
            virtual ~IPositionable() {}

            /*! \brief Gibt die aktuelle Position des Objeckts zurück.
             */
            virtual Position3D getPosition() const = 0;

            /*! \brief Setzt die neue Position des Objekts.
             *  \param position: neue Position
             */
            virtual void setPosition(const Position3D& position) = 0;
        };
    }
}

#endif
