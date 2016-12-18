/*! \file StateLoadGameContent.h
 *  \brief Klasse stellt Schnittstelle für das Laden von spielrelevanten Daten bereit.
 */

#ifndef _STATELOADGAMECONTENT_HEADER
#define _STATELOADGAMECONTENT_HEADER

#include <irrlicht.h>
#include "GameState.h"
#include "LoadingScreen.h"

/*! \class StateLoadGameContent StateLoadGameContent.h "StateLoadGameContent.h"
 *  \brief Schnittstelle für das Laden von spielrelevanten Daten.
 *  \note Instanzierung: `StateLoadGameContent* myStateLoadGameContent = new StateLoadGameContent();`
 * 		  \n Benutzen: `myStateLoadGameContent->update(...);`
 */
class StateLoadGameContent : public GameState
{

public:

    /*! \brief Konstruktor.
     *  \param device (\a IrrlichtDevice*) Zeiger auf das Entchen
     *  \return Zeiger auf das instanzierte Klassenobjekt
     */
    StateLoadGameContent( irr::IrrlichtDevice* device );

	/*! \brief Destruktor
     */
	~StateLoadGameContent();

    /*! \brief Aktualisiert die Startup-Phase des Status.
     *  \param frameDeltaTime (\a const \a f32) Dauer des letzten Frames in Sekunden
     *  \return -
     */
    void start( const irr::f32 frameDeltaTime );

    /*! \brief Aktualisiert die Shutdown-Phase Status.
     *  \param frameDeltaTime (\a const \a f32) Dauer des letzten Frames in Sekunden
     *  \return -
     */
    void shutdown( const irr::f32 frameDeltaTime );

    /*! \brief Aktualisiert den Status.
     *  \param frameDeltaTime (\a const \a f32) Dauer des letzten Frames in Sekunden
     *  \return -
     */
    void update( const irr::f32 frameDeltaTime );

    /*! \brief Zeichnet den Status auf den Bildschirm.
     *  \param -
     *  \return -
     */
    void draw();

    /*! \brief Erweiterung für Eventreceiver, behandelt GUI-Events des Status.
     *  \param event (\a irr::SEvent&) Event-Referenz
     *  \return `true` wenn GUI-Event behandelt wurde, ansonsten `false`
     */
    bool handleGuiEvents( const irr::SEvent& event );

private:

    irr::IrrlichtDevice* device_;
    enum Picture_ {
        LOADING_SCREEN = 0,
        ICON_WORLD,
        ICON_QUESTS,
        ICON_PEOPLE,
        ICON_BUILDINGS,
        ICON_THINGS,
        ICON_HERO,
        ICON_FLORA,
        ICON_FAUNA,
        ICON_WEATHER,
        CONCEPT_1,
        CONCEPT_2,
        CONCEPT_3,
        CONCEPT_4,
        CONCEPT_5,
        CONCEPT_6,
        CONCEPT_7,
        CONCEPT_8,


        COUNT
    };
    irr::core::array<LoadingScreen*> pictures_;
    irr::core::stringc levelName_;
    irr::u32 moduleCounter_;

    StateLoadGameContent( const StateLoadGameContent& );
    StateLoadGameContent& operator=( const StateLoadGameContent& );

    void transitTo( internalState state );

};

#endif
