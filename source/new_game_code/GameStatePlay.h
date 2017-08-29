/*! \file GameStatePlay.h
 *  \brief Klasse stellt Schnittstelle für das eigentliche Spiel bereit.
 */

#ifndef _GAMESTATEPLAY_HEADER
#define _GAMESTATEPLAY_HEADER

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
};

#endif
