/*! \file IGameStateManager.h
 *  \brief Interface für Zugriff auf die verschiedenen Zustände des Spiels.
 *  \note Bestandteil der Leviathan Engine
 */

#ifndef LEVIATHAN_PUBLIC_INTERFACES_CORE_IGAMESTATEMANAGER_H
#define LEVIATHAN_PUBLIC_INTERFACES_CORE_IGAMESTATEMANAGER_H

#include <core/IGameState.h>
#include <cstdint>

namespace leviathan {
    namespace core {

        /*! \interface IGameStateManager
         *  \brief Verwaltung der verschiedenen Zustände des Spiels.
         */
        struct IGameStateManager {
            virtual ~IGameStateManager() {}

            /*! \brief Fügt einen Spielzustand zur Verwaltung hinzu.
             *  \note Existiert die ID wird der existierende Zustand nicht mit dem neuen ersetzt.
             *        Ein bereits vorhandener Zustand kann unter neuer ID erneut hinzugefügt werden.
             *  \attention 0xffffffff ist als ID nicht erlaubt!
             *  \param gameState: zu verwaltender Spielzustand
             *  \param id: Identifikator für späteren Zugriff auf den Zustand
             */
            virtual void add(IGameState& gameState, const uint32_t id) = 0;

            /*! \brief Wechselt zum Spielzustand welcher unter dieser ID abgelegt wurde.
             *  \note Zustände werden übereinander auf einen Stack gelegt.
             *        Ist der Zustand bisher noch nicht im Stack, wird er oben auf den Stack gelegt und aktiviert.
             *        Ist der gewünschte Zustand direkt unter dem aktiven Zustand, wird der aktive Zustand vom Stack
             *        entfernt und der gewünschte Zustand wird wieder aktiviert.
             *        Ist der Zustand bereits aktiv, oder weiter unten im Stack, findet kein Transit statt.
             *  \param id: Identifikator des gewünschten Zustands
             */
            virtual void transitTo(const uint32_t id) = 0;
        };
    }
}

#endif
