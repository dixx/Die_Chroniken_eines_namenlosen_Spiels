/*! \file GameStateManager.h
 *  \brief Klasse stellt Schnittstelle für Zugriff auf die verschiedenen Zustände des Spiels bereit.
 *  \note Bestandteil der Leviathan Engine
 */

#ifndef LEVIATHAN_CORE_GAMESTATEMANAGER_H
#define LEVIATHAN_CORE_GAMESTATEMANAGER_H

#include "IGameState.h"
#include <cstdint>
#include <list>
#include <map>

namespace leviathan {
    namespace core {

        /*! \class GameStateManager GameStateManager.h "GameStateManager.h"
         *  \brief Verwaltung der verschiedenen Zustände des Spiels
         */
        class GameStateManager {

        public:
            /*! \brief Konstruktor.
             */
            GameStateManager() = default;

            /*! \brief Destruktor.
             *  \note Verwaltete Spielzustände werden hier nicht gelöscht.
             */
            ~GameStateManager() = default;

            GameStateManager(const GameStateManager&) = delete;
            GameStateManager& operator=(const GameStateManager&) = delete;

            /*! \brief Fügt einen Spielzustand zur Verwaltung hinzu.
             *  \note Existiert die ID wird der existierende Zustand nicht mit dem neuen ersetzt.
             *        Ein bereits vorhandener Zustand kann unter neuer ID erneut hinzugefügt werden.
             *  \param gameState: zu verwaltender Spielzustand
             *  \param id: Identifikator für späteren Zugriff auf den Zustand
             */
            void add(IGameState& gameState, uint32_t id);

            /*! \brief Wechselt zum Spielzustand welcher unter dieser ID abgelegt wurde.
             *  \note Zustände werden übereinander auf einen Stack gelegt.
             *        Ist der Zustand bisher noch nicht im Stack, wird er oben auf den Stack gelegt und aktiviert.
             *        Ist der gewünschte Zustand direkt unter dem aktiven Zustand, wird der aktive Zustand vom Stack
             *        entfernt und der gewünschte Zustand wird wieder aktiviert.
             *        Ist der Zustand bereits aktiv, oder weiter unten im Stack, findet kein Transit statt.
             *  \param id: Identifikator des gewünschten Zustands
             */
            void transitTo(uint32_t id);

            /*! \brief Aktualisiert den momentan aktiven Zustand.
             *  \param elapsedSeconds: Dauer des letzten Frames in Sekunden
             */
            void update(const float elapsedSeconds);

            /*! \brief Zeichnet den momentan aktiven Zustand auf den Bildschirm.
             */
            void draw();

            /*! \brief Gibt die Anzahl der registrierten Spielzustände zurück.
             *  \attention Nur für Testzwecke gedacht!
             */
            size_t getGameStateCount() const;

            /*! \brief Gibt den Identifikator des aktiven Spielzustands zurück.
             *  \attention Nur für Testzwecke public gemacht!
             *  \note Gibt 0xffffffff zurück wenn kein Zustand aktiv ist.
             */
            uint32_t getActiveStateID();

        private:
            std::map<uint32_t, IGameState*> states_ = std::map<uint32_t, IGameState*>();
            std::list<uint32_t> runningStateIDs_ = std::list<uint32_t>();
        };
    }
}

#endif