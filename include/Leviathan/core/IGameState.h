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

            /*! \brief Wird aufgerufen, wenn der Zustand aktiviert wird.
             *  \note Hier können z.B. Timer reaktiviert oder Anmeldungen am ActionProducer getätigt werden.
             */
            virtual void setActive() = 0;

            /*! \brief Wird aufgerufen, wenn der Zustand deaktiviert wird.
             *  \note Hier können z.B. Timer pausiert oder Abmeldungen vom ActionProducer getätigt werden.
             *  \attention Werden registrierte Aktionen nicht abgemeldet, werden weiterhin Aktions-Events von diesem
             *             Zustand empfangen und verarbeitet. Dies kann zu ungewolltem Verhalten führen!
             */
            virtual void setInactive() = 0;
        };
    }
}
#endif
