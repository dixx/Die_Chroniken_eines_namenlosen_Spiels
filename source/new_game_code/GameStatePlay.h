/*! \file GameStatePlay.h
 *  \brief Klasse stellt Schnittstelle für das eigentliche Spiel bereit.
 */

#ifndef _GAMESTATEPLAY_HEADER
#define _GAMESTATEPLAY_HEADER

#include <irrlicht.h>
#include "leviathan.h"

/*! \class GameStatePlay GameStatePlay.h "GameStatePlay.h"
 *  \brief Schnittstelle für das Spiel.
 */
class GameStatePlay final : public leviathan::core::GameState
{

public:

    /*! \brief Konstruktor.
     */
    GameStatePlay();

    /*! \brief Destruktor
     */
    ~GameStatePlay() final;

    GameStatePlay( const GameStatePlay& ) = delete;
    GameStatePlay& operator=( const GameStatePlay& ) = delete;

    /*! \brief Aktualisiert das Spiel.
     *  \param elapsedSeconds: Dauer des letzten Frames in Sekunden
     */
    void update( const float elapsedSeconds ) final;

    /*! \brief Zeichnet das Spiel auf den Bildschirm.
     */
    void draw() final;

    /*! \brief Behandelt ein GUI-Event.
     *  \param event: zu behandelndes GUI-Event
     *  \return `true` wenn das Event erfolgreich behandelt werden konnte, ansonsten `false`
     */
    bool handleGuiEvent( const irr::SEvent& event ) final;
};

#endif
