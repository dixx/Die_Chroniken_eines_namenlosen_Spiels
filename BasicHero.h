/*! \file BasicHero.h
 *  \brief Klasse stellt Methoden für jeden Helden bereit.
 */

#ifndef _BASICHERO_HEADER
#define _BASICHERO_HEADER

#include <irrlicht.h>
#include "BasicLifeform.h"
#include "Timer.h"

/*! \class BasicHero BasicHero.h "BasicHero.h"
 *  \brief Das braucht jeder Held.
 *  \note Instanzierung: `BasicHero* myBasicHero = new BasicHero();`\n Benutzen: `myBasicHero->moveTo(...);`
 */
class BasicHero : public BasicLifeform
{

public:

    /*! \brief Konstruktor. Erstellt ein komplettes Objekt aus der textuellen Beschreibung des Helden. Wurde er von
     *         einem Child der Klasse aufgerufen, muss sich dieses um die Erstellung kümmern.
     *  \param heroData (\a const \a core::stringc&) textuelle Beschreibung des Helden
     *  \param smgr (\a scene::ISceneManager*) Zeiger auf den SceneManager
     *  \param isParent (\a bool) Bei Vererbung auf `true` setzen, ansonsten automatisch `false`
     *  \return Zeiger auf das instanzierte Klassenobjekt
     */
    BasicHero( const irr::core::stringc& heroData, irr::scene::ISceneManager* smgr, bool isParent = false );

	/*! \brief Destruktor
     */
	~BasicHero();

    /*! \brief Setzt die neue Zielposition des Helden.
     *  \param target (\a const \a core::vector3df) neues Ziel
     *  \param isTriggered (\a const \a bool) Bewegung wird noch aktiv befohlen
     *  \return -
     */
    void moveTo( const irr::core::vector3df target, const bool isTriggered );

#ifdef _DEBUG_MODE
    void toggleSpeed();
#endif

private:

    Timer* traceTimer_;

    BasicHero( const BasicHero& );
    BasicHero& operator=( const BasicHero& );

    inline void init();
    //inline void calculateCollisionRadius();

};

#endif
