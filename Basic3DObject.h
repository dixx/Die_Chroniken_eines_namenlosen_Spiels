/*! \file Basic3DObject.h
 *  \brief Der Grundbaustein aller im Spiel verwendeten 3D-Objekte.
 */

#ifndef _BASIC3DOBJECT_HEADER
#define _BASIC3DOBJECT_HEADER

#include <irrlicht.h>
#include "ObjectParamsExtractor.h"
#include "ObjectConfiguration.h"

using namespace irr;

/*! \class Basic3DObject Basic3DObject.h "Basic3DObject.h"
 *  \brief  Der Grundbaustein für ein Objekt.
 */
class Basic3DObject
{

public:

    /*! \brief Konstruktor. Erstellt ein Basic Objekt aus der textuellen Beschreibung des Kartenteils.
     *  \attention Ist die Beschreibung leer oder fehlerhaft, wird ein leeres Objekt generiert.
     *  \param objectData (\a const \a core::stringc&) textuelle Beschreibung des Objektes
     *  \param smgr (\a scene::ISceneManager*) Zeiger auf den SceneManager
     *  \param isParent (\a bool) Bei Vererbung auf `true` setzen, ansonsten automatisch `false`
     */
    Basic3DObject( const core::stringc& objectData, scene::ISceneManager* smgr, bool isParent = false );

    /*! \brief Destruktor.
     */
    virtual ~Basic3DObject();

    /*! \brief Liefert den Namen des Objektes.
     *  \param -
     *  \return \a const \a core::stringc& Name des Objektes
     */
    const core::stringc& getName() const;

    /*! \brief Liefert den Typ des Objektes.
     *  \param -
     *  \return \a const \a core::stringc& Typ des Objektes
     */
    const core::stringc& getType() const;

    /*! \brief Liefert die aktuelle Konfiguration des Objektes.
     *  \param -
     *  \return \a const \a ObjectConfiguration& Konfiguration des Objektes
     */
    //const ObjectConfiguration& getObjectData() const;

    /*! \brief Liefert die Abmessungen der größten gemeinsamen BoundingBox des Objekts.
     *  \attention Methode ist pure virtual!
     *  \param -
     *  \return \a const \a core::vector3df& Abmessungen größten gemeinsamen BoundingBox des Objekts
     */
    virtual const core::vector3df& getMaxBoundingBoxExtent() const = 0;

    /*! \brief Liefert den Abstand zum Mittelpunkt des Objekts zurück, ab dem Kollisionen abgefangen werden sollen.
     *  \attention Methode ist pure virtual!
     *  \param -
     *  \return \a f32 Kollisionsradius
     */
    virtual f32 getCollisionRadius() const = 0;

    /*! \brief Liefert ein Interface für den Basis-Szenenknoten des Objekts zurück.
     *  \attention Methode ist pure virtual!
     *  \param -
     *  \return \a scene::ISceneNode* Interface auf den Basis-Szenenknoten
     */
    virtual scene::ISceneNode* nodeInterface() const = 0;

    /*! \brief Liefert Länge und Richtung des nächsten Schrittes des Objekts zurück.
     *  \attention Methode ist pure virtual!
     *  \param -
     *  \return \a core::vector3df Länge und Richtung des nächsten Schrittes
     */
    virtual const core::vector3df& getNextStep() const = 0;

protected:

    core::stringc type_;
    core::stringc name_;
    core::stringc objectData_;
    ObjectConfiguration* objectData_2;
    ObjectParamsExtractor* extractor_;
    scene::ISceneManager* smgr_;

    void createLogEntry( const core::stringc& message );
    void deleteExtractor();
    core::vector3df loadScale();
    core::vector3df loadOffset();
    core::vector3df loadRotation();
    core::vector3df loadPosition();
    void loadFilterAndEffects( video::SMaterial& material );
    video::ITexture* loadMainTexture();

private:

    Basic3DObject( const Basic3DObject& );
    void operator=( const Basic3DObject& );

};

#endif
