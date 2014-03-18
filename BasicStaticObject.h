/*! \file BasicStaticObject.h
 \brief Ein statisches Objekt, basierend auf BufferCullMeshSceneNode.
*/

#ifndef _BASICSTATICOBJECT_HEADER
#define _BASICSTATICOBJECT_HEADER

// Linken der IRRLICHT-DLL, nur in VisualStudio nötig
//#ifdef _IRR_WINDOWS_
//    #pragma comment(lib, "Irrlicht.lib")
//#endif

#include <irrlicht.h>
#include "Basic3DObject.h"
#include "BufferCullMeshSceneNode.h"

/*! \class BasicStaticObject BasicStaticObject.h "BasicStaticObject.h"
  \brief  Ein statisches Objekt, basierend auf BufferCullMeshSceneNode.
*/
class BasicStaticObject : public Basic3DObject
{

public:

    /*! \brief Konstruktor. Erstellt ein komplettes Objekt aus der textuellen
               Beschreibung des statischen Objekts. Wurde er von einem Child der
               Klasse aufgerufen, muss sich dieses um die Erstellung kümmern.
      \attention Ist die Beschreibung leer oder fehlerhaft, wird ein leeres
                 Objekt generiert, dessen 3D-Knoten-Zeiger 0 ist.
      \param objectData (\a const \a core::stringc&) textuelle Beschreibung
             des Objekts
      \param smgr (\a scene::ISceneManager*) Zeiger auf den SceneManager
      \param isParent (\a bool) Bei Vererbung auf `true` setzen, ansonsten
             automatisch `false`
    */
    BasicStaticObject(
            const core::stringc& objectData,
            scene::ISceneManager* smgr,
            bool isParent = false
    );

    /*! \brief Destruktor.
    */
    virtual ~BasicStaticObject();

    /*! \brief Liefert einen Zeiger auf den 3D-Knoten des Objekts, oder 0 wenn
               kein Knoten existiert.
      \param -
      \return \a BufferCullMeshSceneNode* Knoten
    */
    BufferCullMeshSceneNode* getNode() const;

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

    /*! \brief Liefert den aktuellen objectData-String des Objekts.
      \param -
      \return \a core::stringc objectData des Objekts
    */
    core::stringc getObjectData();

protected:

    BufferCullMeshSceneNode* node_;

    scene::IMesh* loadMesh();

private:

    core::vector3df nextStep_;

    BasicStaticObject( const BasicStaticObject& );
    void operator=( const BasicStaticObject& );

    void init();

};
// Ende class BasicStaticObject

#endif
// Ende Header-Datei BasicStaticObject
