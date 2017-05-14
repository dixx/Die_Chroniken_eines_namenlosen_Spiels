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
             *  \param gameState: zu verwaltender Spielzustand
             *  \param id: Identifikator für späteren Zugriff auf den State
             */
            void add( GameState& gameState, irr::u32 id );
            //void requestState( GameState& gameState );
            // how to add rules?

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

        private:

            irr::core::map<irr::u32, GameState*> states_;
            irr::core::list<irr::u32> runningStates_;
        };
    }
}

#endif
