/*! \file BasicStaticObject.h
 *  \brief Ein statisches Objekt, basierend auf BufferCullMeshSceneNode.
 */

#ifndef _BASICSTATICOBJECT_HEADER
#define _BASICSTATICOBJECT_HEADER

#include <irrlicht.h>
#include "Basic3DObject.h"
#include "BufferCullMeshSceneNode.h"

using namespace irr;

/*! \class BasicStaticObject BasicStaticObject.h "BasicStaticObject.h"
 *  \brief  Ein statisches Objekt, basierend auf BufferCullMeshSceneNode.
 */
class BasicStaticObject : public Basic3DObject
{

public:

    /*! \brief Konstruktor. Erstellt ein komplettes Objekt aus der textuellen Beschreibung des statischen Objekts.
     *         Wurde er von einem Child der Klasse aufgerufen, muss sich dieses um die Erstellung kümmern.
     *  \attention Ist die Beschreibung leer oder fehlerhaft, wird ein leeres Objekt generiert, dessen
     *             3D-Knoten-Zeiger 0 ist.
     *  \param objectData (\a const \a core::stringc&) textuelle Beschreibung des Objekts
     *  \param smgr (\a scene::ISceneManager*) Zeiger auf den SceneManager
     *  \param isParent (\a bool) Bei Vererbung auf `true` setzen, ansonsten automatisch `false`
     */
    BasicStaticObject( const core::stringc& objectData, scene::ISceneManager* smgr, bool isParent = false );

    /*! \brief Destruktor.
     */
    virtual ~BasicStaticObject();

    /*! \brief Liefert einen Zeiger auf den 3D-Knoten des Objekts, oder 0 wenn kein Knoten existiert.
     *  \param -
     *  \return \a BufferCullMeshSceneNode* Knoten
     */
    BufferCullMeshSceneNode* getNode() const;

    /*! \brief Liefert den Abstand zum Mittelpunkt des Objekts zurück, ab dem Kollisionen abgefangen werden sollen.
     *  \param -
     *  \return \a const \a f32 Kollisionsradius
     */
    f32 getCollisionRadius() const;

    /*! \brief Liefert ein Interface für den Basis-Szenenknoten des Objekts zurück.
     *  \param -
     *  \return \a scene::ISceneNode* Interface auf den Basis-Szenenknoten
     */
    scene::ISceneNode* nodeInterface() const;

    /*! \brief Liefert Länge und Richtung des nächsten Schrittes des Objekts zurück.
     *  \param -
     *  \return \a core::vector3df Länge und Richtung des nächsten Schrittes
     */
    const core::vector3df& getNextStep() const;

    /*! \brief Liefert die Abmessungen der größten gemeinsamen BoundingBox des Objekts.
     *  \param -
     *  \return \a const \a core::vector3df& Abmessungen größten gemeinsamen BoundingBox des Objekts
     */
    const core::vector3df& getMaxBoundingBoxExtent() const;

    /*! \brief Liefert die aktuelle Konfiguration des Objektes.
     *  \param -
     *  \return \a const \a ObjectConfiguration& Konfiguration des Objektes
     */
    //const ObjectConfiguration& getObjectData() const;

protected:

    BufferCullMeshSceneNode* node_;
    core::vector3df maxBBExtent_;

    scene::IMesh* loadMesh();

private:

    BasicStaticObject( const BasicStaticObject& );
    void operator=( const BasicStaticObject& );

    void init();

};

#endif
