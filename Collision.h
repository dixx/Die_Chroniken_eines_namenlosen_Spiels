/*! \file Collision.h
 *  \brief Klasse (Singleton) stellt Schnittstelle für Kollisionserkennung bereit.
 */

#ifndef _COLLISION_HEADER
#define _COLLISION_HEADER

#include <irrlicht.h>
#include "Basic3DObject.h"

using namespace irr;

/*! \class Collision Collision.h "Collision.h"
 *  \brief  Schnittstelle zur Collision Detection. Diese Klasse enthält Funktionen für das Erkennen und Behandeln
 *          von Kollisionen mit Meshes.
 *  \attention Klasse ist \c `Singleton`.
 *  \note Instanzierung: `Collision& myCollision = Collision::getInstance();` \n Oder: `Collision::getInstance();`
 *        \n Benutzen: `myCollision.isMouseIntersectingWithWorld();`
 *        \n Oder: `Collision::getInstance().removeNodeFromWorld(...);`
 */
class Collision
{

public:

    core::vector3df collisionPoint;  //!< von Kollision betroffener Punkt
    core::triangle3df collisionTriangle;  //!< von Kollision betroffenes Dreieck
    scene::ISceneNode* collisionNode;  //!< Zeiger auf den von Kollision betroffenen Szenenknoten;
                                       //!  Seit Irrlicht 1.8 nicht mehr const.
    core::vector3df collisionDodgeVector;  //!< Ausweich-Vektor

    /*! \brief Ersatz für den Konstruktor.
     *
     *  Instanziert die Klasse einmalig und verhindert Mehrfachinstanzierung.
     *  \param sceneManager (\a scene::ISceneManager*) Zeiger auf den aktuellen SzenenManager des Entchens
     *  \return Referenz auf die einzige Instanz dieser Klasse
     */
    static Collision& getInstance( scene::ISceneManager* sceneManager = 0 );

    /*! \brief Fügt statisches Mesh zur Kollisionserkennung hinzu.
     *  \attention Mesh darf sich keinesfalls verändern!
     *  \param node (\a scene::IMeshSceneNode*) statischer Szenenknoten
     *  \return -
     */
    void addStaticMeshNodeToWorld( scene::IMeshSceneNode* node );

    /*! \brief Fügt animiertes Mesh zur Kollisionserkennung hinzu.
     *  \param node (\a scene::IAnimatedMeshSceneNode*) animierter Szenenknoten
     *  \return -
     */
    void addAnimatedMeshNodeToWorld( scene::IAnimatedMeshSceneNode* node );

    /*! \brief Entfernt Mesh aus der Kollisionserkennung.
     *  \param node (\a scene::ISceneNode*) Szenenknoten
     *  \return -
     */
    void removeNodeFromWorld( scene::ISceneNode* node );

    /*! \brief Fügt beliebiges Objekt zur "schnellen" Kollisionserkennung (im Sichtradius des Helden) hinzu.
     *  \param object (\a Basic3DObject*) Objekt
     *  \return -
     */
    void addObjectToRangedDetection( Basic3DObject* object );

    /*! \brief Entfernt beliebiges Objekt aus "schneller" Kollisionserkennung (im Sichtradius des Helden).
     *  \param object (\a Basic3DObject*) Objekt
     *  \return -
     */
    void removeObjectFromRangedDetection( Basic3DObject* object );

    /*! \brief Prüft ob unter dem Mauspfeil ein Knoten liegt.
     *  \param -
     *  \return `true` wenn ein Knoten getroffen wurde, ansonsten `false`
     */
    bool isMouseIntersectingWithWorld();

    /*! \brief Abfrage, ob ein Strahl durch irgendeinen Knoten durchgeht.
     *  \param ray (\a core::line3df&) ein 3D-Strahl
     *  \param rootNode (\a scene::ISceneNode*) Startknoten für Suche
     *  \return `true` wenn ein Knoten getroffen wurde, ansonsten `false`
     */
    bool isRayIntersectingWithWorld( const core::line3df& ray, scene::ISceneNode* rootNode );

    /*! \brief Abfrage, ob ein Strahl durch irgendeinen Knoten durchgeht, der im Sichtbereich des Helden liegt und
     *         begehbar ist.
     *  \param ray (\a core::line3df&) ein 3D-Strahl
     *  \return `true` wenn ein Knoten getroffen wurde, ansonsten `false`
     */
    bool isRayIntersectingWithWalkableNodesAroundHero( const core::line3df& ray );

    /*! \brief Abfrage, ob ein Objekt mit irgendeinem Knoten kollidiert.
     *  \param object (\a Basic3DObject*) Objekt
     *  \return `true` wenn eine Kollision vorliegt, ansonsten `false`
     */
    bool isObjectCollidingWithNodes( Basic3DObject* object );

    /*! \brief Entfernt alle Triangleselektoren.
     *  \param -
     *  \return -
     */
    void clearRemainingSelectors();

#ifdef _DEBUG_MODE
    u32 loadedSelectors();
#endif

private:

    scene::ISceneManager* smgr_;
    scene::ISceneCollisionManager* colliman_;
    scene::ITriangleSelector* selector_;
    scene::IMetaTriangleSelector* walkableSelector_;
    core::list<Basic3DObject*> collidableObjects_;
    core::list<Basic3DObject*>::Iterator iter_;

    Collision( scene::ISceneManager* sceneManager );
    Collision( const Collision& );
    Collision& operator=( const Collision& );
    ~Collision();

};

#endif
