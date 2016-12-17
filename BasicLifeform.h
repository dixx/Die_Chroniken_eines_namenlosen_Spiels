/*! \file BasicLifeform.h
 *  \brief Ein Lebewesen.
 */

#ifndef _BASICLIFEFORM_HEADER
#define _BASICLIFEFORM_HEADER

#include <irrlicht.h>
#include "Basic3DObject.h"

/*! \class BasicLifeform BasicLifeform.h "BasicLifeform.h"
 *  \brief Ein Lebewesen.
 */
class BasicLifeform : public Basic3DObject
{

public:

    /*! \brief Konstruktor. Erstellt ein komplettes Objekt aus der textuellen Beschreibung des Lebewesens.
     *         Wurde er von einem Child der Klasse aufgerufen, muss sich dieses um die Erstellung kümmern.
     *  \attention Ist die Beschreibung leer oder fehlerhaft, wird ein leeres Objekt generiert, dessen
     *             3D-Knoten-Zeiger 0 ist.
     *  \param objectData (\a const \a core::stringc&) textuelle Beschreibung des Lebewesens
     *  \param smgr (\a scene::ISceneManager*) Zeiger auf den SceneManager
     *  \param isParent (\a bool) Bei Vererbung auf `true` setzen, ansonsten automatisch `false`
     */
    BasicLifeform( const irr::core::stringc& objectData, irr::scene::ISceneManager* smgr, bool isParent = false );

    /*! \brief Destruktor.
     */
    virtual ~BasicLifeform();

    /*! \brief Setzt z.B. die neue Position und weitere Attribute des Lebewesens.
     *  \param frameDeltaTime (\a const \a f32) Dauer des letzten Frames in Sekunden
     *  \return -
     */
    virtual void update( const irr::f32 frameDeltaTime );

    /*! \brief Setzt die neue Zielposition des Lebewesens.
     *  \param target (\a const \a core::vector3df) neues Ziel
     *  \return -
     */
    virtual void moveTo( const irr::core::vector3df target );

    /*! \brief Liefert einen Zeiger auf den 3D-Knoten des Lebewesens, oder 0 wenn kein Knoten existiert.
     *  \param -
     *  \return \a scene::IAnimatedMeshSceneNode* Knoten
     */
    irr::scene::IAnimatedMeshSceneNode* getNode() const;

    /*! \brief Liefert den Abstand zum Mittelpunkt des Lebewesens zurück, ab dem Kollisionen abgefangen werden sollen.
     *  \param -
     *  \return \a const \a f32 Kollisionsradius
     */
    irr::f32 getCollisionRadius() const;

    /*! \brief Liefert ein Interface für den Basis-Szenenknoten des Lebewesens zurück.
     *  \param -
     *  \return \a scene::ISceneNode* Interface auf den Basis-Szenenknoten
     */
    irr::scene::ISceneNode* nodeInterface() const;

    /*! \brief Liefert Länge und Richtung des nächsten Schrittes des Lebewesens zurück.
     *  \param -
     *  \return \a core::vector3df Länge und Richtung des nächsten Schrittes
     */
    const irr::core::vector3df& getNextStep() const;

    /*! \brief Liefert die Abmessungen der größten gemeinsamen BoundingBox des Lebewesens.
     *  \param -
     *  \return \a const \a core::vector3df& Abmessungen der größten gemeinsamen BoundingBox des Lebewesens
     */
    const irr::core::vector3df& getMaxBoundingBoxExtent() const;

protected:

    irr::scene::IAnimatedMeshSceneNode* node_;
    bool isMoving_;
    bool wasMoving_;
    irr::f32 speed_;
    irr::f32 movementDelta_;
    irr::f32 collisionRadius_;
    irr::core::vector3df currentPosition_;
    irr::core::vector3df targetPosition_;
    irr::core::vector3df positionOffset_;
    irr::core::vector3df rotation_;
    irr::core::vector3df nextStep_;
    irr::core::vector3df maxBBExtent_;
    irr::f32 maxJumpHeight_;

    irr::scene::IAnimatedMesh* loadMesh();
    void calculateNextStep();
    inline void calculateCollisionRadius();
    void updateMovement();
    inline void stopMovement();

private:

    BasicLifeform( const BasicLifeform& );
    void operator=( const BasicLifeform& );

    void init();

};

#endif
