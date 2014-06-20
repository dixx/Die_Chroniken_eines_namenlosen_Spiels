/*! \file Hero.h
 *  \brief Klasse stellt Schnittstelle für den Helden bereit.
 */

#ifndef _HERO_HEADER
#define _HERO_HEADER

#include <irrlicht.h>
#include "BasicHero.h"

using namespace irr;

/*! \class Hero Hero.h "Hero.h"
 *  \brief Schnittstelle für den Helden.
 *  \attention Klasse ist `Singleton`.\n Ein Zeiger auf eine Instanz des Irrlicht-SceneManagers wird benötigt.
 *  \note Instanzierung: `<c>Hero& myHero = Hero::getInstance();` \n Oder: `Hero::getInstance();`
 *        \n Benutzen: `myHero.load(...);` \n Oder: `Hero::getInstance().load(...);`
 */
class Hero
{

public:

    /*! \brief Ersatz für den Konstruktor.
     *
     *  Instanziert die Klasse einmalig und verhindert Mehrfachinstanzierung.
     *  \param sceneManager (\a ISceneManager*) Zeiger auf den SceneManager
     *  \return Referenz auf die einzige Instanz dieser Klasse
     */
    static Hero& getInstance( scene::ISceneManager* sceneManager = 0 );

    /*! \brief Lädt einen Helden.
     *  \param -
     *  \return -
     */
    void load();

    /*! \brief Entlädt den Helden.
     *  \param -
     *  \return -
     */
    void unload();

    /*! \brief Gibt einen Zeiger auf den geladenen Helden zurück.
     *  \param -
     *  \return Zeiger auf den Helden
     */
    BasicHero* current();

private:

    scene::ISceneManager* smgr_;
    BasicHero* hero_;

    Hero( scene::ISceneManager* smgr );
    Hero( const Hero& );
    Hero& operator=( const Hero& );
    ~Hero();

};

#endif
