/*! \file TransitionGameState.h
 *  \brief Klasse stellt Schnittstelle für Spiel-Übergangs-Stati bereit.
 */

#ifndef _TRANSITIONGAMESTATE_HEADER
#define _TRANSITIONGAMESTATE_HEADER

#include <irrlicht.h>
#include "GameState.h"

using namespace irr;

/*! \class TransitionGameState TransitionGameState.h "TransitionGameState.h"
 *  \brief Schnittstelle für Spiel-Übergangs-Stati.
 *  \note Instanzierung: `TransitionGameState* myTransitionGameState = new TransitionGameState();`
 *  \n Benutzen: `myTransitionGameState->xxxx();`
 */
class TransitionGameState : public GameState
{

protected:

	// Variablen

    /*! \brief Konstruktor.
     *  \param -
     *  \return Zeiger auf das instanzierte Klassenobjekt
     */
    TransitionGameState();

    /*! \brief Destruktor.
     */
    ~TransitionGameState();

    //void method( type param );

private:

	//Vars

    TransitionGameState( const TransitionGameState& );
    TransitionGameState& operator=( const TransitionGameState& );

};

#endif
