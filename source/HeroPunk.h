/*! \file HeroPunk.h
 *  \brief Klasse stellt die Charakterklasse Punk bereit.
 */

#ifndef _HEROPUNK_HEADER
#define _HEROPUNK_HEADER

#include <irrlicht.h>
#include "BasicHero.h"

/*! \class HeroPunk HeroPunk.h "HeroPunk.h"
 *  \brief Der Punk.
 *  \note Instanzierung: `HeroPunk* myHeroPunk = new HeroPunk();` \n Benutzen: `myHeroPunk->xxxx();`
 */
class HeroPunk : public BasicHero
{

public:

    /*! \brief Konstruktor. Erstellt einen Punk.
     *  \param punkData (\a const \a core::stringc&) textuelle Beschreibung des Punk
     *  \param smgr (\a scene::ISceneManager*) Zeiger auf den SceneManager
     *  \return Zeiger auf das instanzierte Klassenobjekt
     */
    HeroPunk( const irr::core::stringc& punkData, irr::scene::ISceneManager* smgr );

	/*! \brief Destruktor
     */
	~HeroPunk();

    /*! \brief Liefert den aktuellen objectData-String des Punk.
     *  \param -
     *  \return \a core::stringc objectData des Punk
     */
    irr::core::stringc getObjectData();


private:

    HeroPunk( const HeroPunk& );
    HeroPunk& operator=( const HeroPunk& );

    inline void init();

};

#endif
