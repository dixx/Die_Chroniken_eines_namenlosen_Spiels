/*! \file GameStateManager.h
 *  \brief Klasse stellt Schnittstelle für Zugriff auf die verschiedenen Zustände des Spiels bereit.
 */

#ifndef _LEVIATHAN_GAMESTATEMANAGER_HEADER
#define _LEVIATHAN_GAMESTATEMANAGER_HEADER

#include <irrlicht.h>
#include "GameState.h"

namespace leviathan
{
    namespace core
    {

        /*! \class GameStateManager GameStateManager.h "GameStateManager.h"
         *  \brief Verwaltung der verschiedenen Zustände des Spiels
         */
        class GameStateManager
        {
        public:

            /*! \brief Konstruktor.
             */
            GameStateManager();

            /*! \brief Destruktor.
             */
            ~GameStateManager();

            GameStateManager( const GameStateManager& ) = delete;
            GameStateManager& operator=( const GameStateManager& ) = delete;

            /*! \brief Fügt einen Spielzustand zur Verwaltung hinzu.
             *  \note Existiert die ID wird der existierende Zustand nicht mit dem neuen ersetzt.
             *        Ein bereits vorhandener Zustand kann unter neuer ID erneut hinzugefügt werden.
             *  \param gameState: zu verwaltender Spielzustand
             *  \param id: Identifikator für späteren Zugriff auf den Zustand
             */
            void add( GameState& gameState, irr::u32 id );

            /*! \brief Wechselt zum Spielzustand welcher unter dieser ID abgelegt wurde.
             *  \note Zustände werden übereinander auf einen Stack gelegt.
             *        Ist der Zustand bisher noch nicht im Stack, wird er oben auf den Stack gelegt und aktiviert.
             *        Ist der gewünschte Zustand direkt unter dem aktiven Zustand, wird der aktive Zustand vom Stack
             *        entfernt und der gewünschte Zustand wird wieder aktiviert.
             *        Ist der Zustand bereits aktiv, oder weiter unten im Stack, findet kein Transit statt.
             *  \param id: Identifikator des gewünschten Zustands
             */
            void transitTo( irr::u32 id );

            /*! \brief Aktualisiert den momentan aktiven Zustand.
             *  \param frameDeltaTime: Dauer des letzten Frames in Sekunden
             */
            void update( const irr::f32 frameDeltaTime );

            /*! \brief Zeichnet den momentan aktiven Zustand auf den Bildschirm.
             */
            void draw();

            /*! \brief Gibt die Anzahl der registrierten Spielzustände zurück.
             *  \attention Nur für Testzwecke gedacht!
             */
            unsigned int getGameStateCount();

            /*! \brief Gibt den Identifikator des aktiven Spielzustands zurück.
             *  \attention Nur für Testzwecke gedacht!
             */
            irr::u32 getActiveStateID();

        private:

            irr::core::map<irr::u32, GameState*> states_;
            irr::core::list<irr::u32> runningStates_;
        };
    }
}

#endif
