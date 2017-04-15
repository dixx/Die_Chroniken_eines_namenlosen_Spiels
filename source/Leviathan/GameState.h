/*! \file GameState.h
 *  \brief Klasse stellt Interfacemethoden für Spielzustände bereit.
 */

#ifndef _GAMESTATE_HEADER
#define _GAMESTATE_HEADER

#include <irrlicht.h>

namespace leviathan
{
    namespace core
    {

        /*! \class GameState GameState.h "GameState.h"
         *  \brief Interface für Spielzustände.
         *  \attention Klasse ist nur zum Erben für Implementationen verschiedener Spielzustände gedacht.
         */
        class GameState
        {

        public:

            /*! \brief Konstruktor.
             */
            GameState() {};

            /*! \brief Destruktor.
             */
        	virtual ~GameState() {};

            /*! \brief Aktualisiert den Zustand.
             *  \param frameDeltaTime: Dauer des letzten Frames in Sekunden
             */
            virtual void update( const irr::f32 frameDeltaTime ) = 0;

            /*! \brief Zeichnet den Zustand auf den Bildschirm.
             */
            virtual void draw() = 0;

            /*!
             *
             */
            //virtual void pause() = 0;

            /*!
             *
             */
            //virtual void resume() = 0;

        protected:

            // internalState currentInternalState_;
            // bool forceDraw_;

        private:

            GameState( const GameState& );
            GameState& operator=( const GameState& );
        };
    }
}
#endif
