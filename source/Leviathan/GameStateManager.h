/*! \file GameStateManager.h
 *  \brief Klasse stellt Schnittstelle für Zugriff auf die verschiedenen Zustände des Spiels bereit.
 */

#ifndef _GAMESTATEMANAGER_HEADER
#define _GAMESTATEMANAGER_HEADER

#include "leviathan.h"
#include "GameState.h"

class GameState; // forward declaration

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

            /*! \brief Fügt einen Spielzustand zur Verwaltung hinzu.
             *  \param gameState: zu verwaltender Spielzustand
             */
            void add( Gamestate& gameState );
            //void requestState( Gamestate& gameState );
            // how to add rules?

            /*! \brief Aktualisiert den momentan aktiven Zustand.
             *  \param frameDeltaTime: Dauer des letzten Frames in Sekunden
             */
            void update( const irr::f32 frameDeltaTime );

            /*! \brief Zeichnet den momentan aktiven Zustand auf den Bildschirm.
             */
            void draw();

        private:

            GameStateManager( const GameStateManager& );
            GameStateManager& operator=( const GameStateManager& );
        };
    }
}

#endif
