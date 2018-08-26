/*! \file GameState.h
 *  \brief Klasse stellt Interfacemethoden für Spielzustände bereit.
 *  \note Bestandteil der Leviathan Engine
 */

#ifndef _LEVIATHAN_GAMESTATE_HEADER
#define _LEVIATHAN_GAMESTATE_HEADER

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

            GameState(const GameState&) = delete;
            GameState& operator=(const GameState&) = delete;

            /*! \brief Aktualisiert den Zustand.
             *  \param elapsedSeconds: Dauer des letzten Frames in Sekunden
             */
            virtual void update(const float elapsedSeconds) = 0;

            /*! \brief Zeichnet den Zustand auf den Bildschirm.
             */
            virtual void draw() = 0;

            /*! \brief Behandelt ein GUI-Event.
             *  \param event: zu behandelndes GUI-Event
             *  \return `true` wenn das Event erfolgreich behandelt werden konnte, ansonsten `false`
             */
            virtual bool handleGuiEvent(const irr::SEvent& event) = 0;
        };
    }
}
#endif
