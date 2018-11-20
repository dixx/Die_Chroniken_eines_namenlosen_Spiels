/*! \file IGameState.h
 *  \brief Interface für Spielzustände.
 *  \note Bestandteil der Leviathan Engine
 */

#ifndef LEVIATHAN_CORE_IGAMESTATE_H
#define LEVIATHAN_CORE_IGAMESTATE_H

namespace leviathan {
    namespace core {

        /*! \interface IGameState
         *  \brief Interface für Spielzustände.
         */
        struct IGameState {

            virtual ~IGameState() {}

            /*! \brief Aktualisiert den Zustand.
             *  \param elapsedSeconds: Dauer des letzten Frames in Sekunden
             */
            virtual void update(const float elapsedSeconds) = 0;

            /*! \brief Zeichnet den Zustand auf den Bildschirm.
             */
            virtual void draw() = 0;
        };
    }
}
#endif
