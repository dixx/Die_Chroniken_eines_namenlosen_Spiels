/*! \file BasicLifeform.h
  \brief Ein Lebewesen.
*/

#ifndef _BASICLIFEFORM_HEADER
#define _BASICLIFEFORM_HEADER

#include "Basic3DObject.h"

/*! \class BasicLifeform BasicLifeform.h "BasicLifeform.h"
  \brief Ein Lebewesen.
*/
class BasicLifeform : public Basic3DObject
{

public:

    /*! \brief Konstruktor. Erstellt ein komplettes Objekt aus der textuellen
               Beschreibung des Lebewesens. Wurde er von einem Child der
               Klasse aufgerufen, muss sich dieses um die Erstellung kümmern.
      \attention Ist die Beschreibung leer oder fehlerhaft, wird ein leeres
                 Objekt generiert, dessen 3D-Knoten-Zeiger 0 ist.
      \param objectData (\a const \a core::stringc&) textuelle Beschreibung
             des Objekts
      \param smgr (\a scene::ISceneManager*) Zeiger auf den SceneManager
      \param isParent (\a bool) Bei Vererbung auf `true` setzen, ansonsten
             automatisch `false`
    */
    BasicLifeform(
            const core::stringc& objectData,
            scene::ISceneManager* smgr,
            bool isParent = false
    );

    /*! \brief Destruktor.
    */
    virtual ~BasicLifeform();

    /*! \brief Setzt z.B. die neue Position und weitere Attribute des
               Lebewesens.
      \param frameDeltaTime (\a const \a f32) Dauer des letzten Frames in
             Sekunden
      \return -
    */
    virtual void update( const f32 frameDeltaTime );

    /*! \brief Liefert einen Zeiger auf den 3D-Knoten des Objekts, oder 0 wenn
               kein Knoten existiert.
      \param -
      \return \a scene::IAnimatedMeshSceneNode* Knoten
    */
    scene::IAnimatedMeshSceneNode* getNode() const;

    /*! \brief Liefert den Abstand zum Mittelpunkt des Objekts zurück, ab dem
               Kollisionen abgefangen werden sollen.
      \param -
      \return \a const \a f32 Kollisionsradius
    */
    f32 getCollisionRadius() const;

    /*! \brief Liefert ein Interface für den Basis-Szenenknoten des Objekts
               zurück.
      \param -
      \return \a scene::ISceneNode* Interface auf den Basis-Szenenknoten
    */
    scene::ISceneNode* nodeInterface() const;

    /*! \brief Liefert Länge und Richtung des nächsten Schrittes des Objekts
               zurück.
      \param -
      \return \a core::vector3df Länge und Richtung des nächsten Schrittes
    */
    const core::vector3df& getNextStep() const;

protected:

    scene::IAnimatedMeshSceneNode* node_;
    bool isMoving_;
    bool wasMoving_;
    f32 speed_;
    f32 movementDelta_;
    f32 collisionRadius_;
    core::vector3df nextStep_;

    scene::IAnimatedMesh* loadMesh();

private:

    BasicLifeform( const BasicLifeform& );
    void operator=( const BasicLifeform& );

    void init();
    void calculateNextStep();
    inline void calculateCollisionRadius();

};
// Ende class BasicLifeform

#endif
// Ende Header-Datei BasicLifeform
