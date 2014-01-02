/*! \file Hero.h
  \brief Klasse stellt Schnittstelle für den Helden bereit.
*/

#ifndef _HERO_HEADER
#define _HERO_HEADER

// Linken der IRRLICHT-DLL, nur in VisualStudio nötig
//#ifdef _IRR_WINDOWS_
//    #pragma comment(lib, "Irrlicht.lib")
//#endif

#include <irrlicht.h>
#include "BasicLifeform.h"
#include "Timer.h"

using namespace irr;
// Die innenliegenden Namespaces "core", "video" usw. werden im Folgenden
// immer explizit angegeben, um den Überblick zu behalten.

/*! \class Hero Hero.h "Hero.h"
  \brief Schnittstelle für den Helden.
  \note Instanzierung: `Hero* myHero = new Hero();`
		\n Benutzen: `myHero->moveTo(...);`
*/
class Hero : public BasicLifeform
{

public:

    /*! \brief Konstruktor.
      \param objectData (\a const \a core::stringc&) textuelle Beschreibung
             des Helden
      \param sceneManager (\a scene::ISceneManager*) aktiver Scene-Manager
      \return Zeiger auf das instanzierte Klassenobjekt
    */
    Hero( const core::stringc& objectData, scene::ISceneManager* sceneManager );

	// Destruktor
	~Hero();

    //! \brief Lädt einen Helden.
    //! \param -
    //! \return -
    // replace!
    void load();

    //! \brief Entlädt den Helden.
    //! \param -
    //! \return -
    // replace!
    void unload();

    //! \brief Setzt die neue Position und weitere Attribute des Helden.
    //! \param frameDeltaTime (\a const \a f32) Dauer des letzten Frames in
    //!        Sekunden
    //! \return -
    void update( const f32 frameDeltaTime );

    //! \brief Setzt die neue Zielposition des Helden.
    //! \param target (\a const \a core::vector3df) neues Ziel
    //! \param isTriggered (\a const \a bool) Bewegung wird noch aktiv befohlen
    //! \return -
    void moveTo( const core::vector3df target, const bool isTriggered );

#ifdef _DEBUG_MODE
    void toggleSpeed();
#endif

private:

    scene::ISceneManager* smgr_;
    scene::IAnimatedMeshSceneNode* node_;
    core::vector3df currentPosition_;
    core::vector3df targetPosition_;
    core::vector3df lastPosition_;
    core::vector3df nextStep_;
    core::vector3df positionOffset_;
    core::vector3df scale_;
    core::vector3df rotation_;
    bool heroIsMoving_;
    bool heroWasMoving_;
    f32 speed_;
    f32 movementDelta_;
    Timer* traceTimer_;
    f32 maxJumpHeight_;
    f32 collisionRadius_;

    Hero( const Hero& );
    Hero& operator=( const Hero& );

    void calculateNextStep();
    inline void calculateCollisionRadius();
    void updateMovement();
    inline void stopMovement();

};
// Ende class Hero

#endif
// Ende Header-Datei Hero
