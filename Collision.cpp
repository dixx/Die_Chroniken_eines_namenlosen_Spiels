#include "Collision.h"
#include "Constants.h"
#include "Debugwindow.h"
#include "Eventreceiver.h"
//#include "Hero.h"
#include "Logfile.h"
//#include "ObjectManager.h"
#include "Zufall.h"



Collision& Collision::getInstance( scene::ISceneManager* sceneManager )
{
    static Collision _instance( sceneManager );
    return _instance;
}



void Collision::addStaticMeshNodeToWorld( scene::IMeshSceneNode* node )
{
    // todo minimalPolysPerNode anpassen
    // DEPRECATED since 1.7.2
    //this->selector = smgr->createOctTreeTriangleSelector(
    selector_ = smgr_->createOctreeTriangleSelector(
            node->getMesh(),
            node,
            900
    );
    node->setTriangleSelector( selector_ );
    selector_ = 0;
}



void Collision::addAnimatedMeshNodeToWorld(
        scene::IAnimatedMeshSceneNode* node )
{
    selector_ = smgr_->createTriangleSelector( node );
    node->setTriangleSelector( selector_ );
    selector_ = 0;
}



void Collision::removeNodeFromWorld( scene::ISceneNode* node )
{
    scene::ITriangleSelector* sel = node->getTriangleSelector();
    if ( sel )
    {
        node->setTriangleSelector( 0 );
        sel->drop();
    }
}



void Collision::addObjectToRangedDetection( Basic3DObject* object )
{
    if ( object->nodeInterface()->getID() & ID_FLAG_BEGEHBAR )
    {
        walkableSelector_->addTriangleSelector(
                object->nodeInterface()->getTriangleSelector() );
    }
    if ( object->nodeInterface()->getID() & ID_FLAG_KOLLIDIERBAR )
    {
        collidableObjects_.push_back( object );
    }
}



void Collision::removeObjectFromRangedDetection( Basic3DObject* object )
{
    if ( object->nodeInterface()->getID() & ID_FLAG_BEGEHBAR )
    {
        walkableSelector_->removeTriangleSelector(
                object->nodeInterface()->getTriangleSelector() );
    }
    if ( object->nodeInterface()->getID() & ID_FLAG_KOLLIDIERBAR )
    {
        for( iter_ = collidableObjects_.begin();
                iter_ != collidableObjects_.end(); ++iter_ )
        {
            if( *iter_ == object )
            {
                collidableObjects_.erase( iter_ );
                break;
            }
        }
    }
}



bool Collision::isRayIntersectingWithWorld( const core::line3df& ray,
        scene::ISceneNode* rootNode )
{
    // collides smart
    collisionNode = colliman_->getSceneNodeAndCollisionPointFromRay(
            ray,
            collisionPoint,
            collisionTriangle,
            rootNode->getID(), // Nur Knoten mit entsprechender ID (BitMask)
            rootNode,
            true //Debug-Objekte nicht behandeln
    );
    return ( collisionNode ) ? true: false;
}



bool Collision::isRayIntersectingWithWalkableNodesAroundHero(
        const core::line3df& ray )
{
    // collides directly with the triangles
    return colliman_->getCollisionPoint(
            ray,
            walkableSelector_,
            collisionPoint,
            collisionTriangle,
            collisionNode
    );
}


// todo refactor so that any movable object can be used!
//bool Collision::isHeroCollidingWithNodes()
//{
//    bool isCollision = false;
//    Hero& hero = Hero::getInstance();
//    scene::IAnimatedMeshSceneNode* heroNode = hero.getNode();
//    f32 heroRadius = hero.getCollisionRadius();
//    const core::vector3df& heroCenter = heroNode->getAbsolutePosition();
//    core::aabbox3df heroBB = core::aabbox3df(
//            heroCenter - heroRadius, heroCenter + heroRadius );
//#ifdef _DEBUG_MODE
//    heroNode->setMaterialFlag( video::EMF_POINTCLOUD, false );
//#endif
//    Basic3DObject* object = 0;
//    scene::ISceneNode* objectNode = 0;
//    f32 objectRadius = 0.0f;
//    f32 minDistance = 0.0f;
//    core::vector3df distance;
//    for( iter_ = collidableObjects_.begin(); iter_ != collidableObjects_.end();
//            ++iter_ )
//    {
//        object = *iter_;
//        objectNode = object->nodeInterface();
//        objectRadius = object->getCollisionRadius();
//        if ( objectRadius > core::ROUNDING_ERROR_f32 ) // Lebewesen?
//        {
//            minDistance = heroRadius + objectRadius;
//            distance = objectNode->getAbsolutePosition() - heroCenter;
//            distance.Y = 0.0f;
//            if ( ( distance.getLength() - minDistance ) < 0.0f )
//            {
//                isCollision = true;
//                collisionDodgeVector = distance
//                        - core::vector3df( distance ).setLength(
//                                minDistance + 0.01f )
//                        + hero.getNextStep();
//            }
//        }
//        else
//        {
//            if( objectNode->getTransformedBoundingBox().intersectsWithBox(
//                    heroBB ) )
//            {
//#ifdef _DEBUG_MODE
//                heroNode->setMaterialFlag( video::EMF_POINTCLOUD, true );
//#endif
//                isCollision = true;
//                collisionDodgeVector = hero.getNextStep();
//            }
//        }
//        if ( isCollision )
//        {
//#ifdef _DEBUG_MODE
//            Debugwindow::getInstance().addLine( L"collision with: ",
//                    object->getName() );
//            Debugwindow::getInstance().addLine( L"HeroCollisionRadius: ",
//                    heroRadius );
//            Debugwindow::getInstance().addLine( L"ObjectCollisionRadius: ",
//                    object->getCollisionRadius() );
//#endif
//            return true;
//        }
//    }
//    return false;
//}



//bool Collision::isMouseIntersectingWithWorld()
//{
//    return isRayIntersectingWithWorld(
//            colliman_->getRayFromScreenCoordinates(
//                    core::position2di(
//                            Eventreceiver::getInstance().getMouseX(),
//                            Eventreceiver::getInstance().getMouseY()
//                    ),
//                    smgr_->getActiveCamera()
//            ),
//            ObjectManager::getInstance().nodesRespondingToMouse
//    );
//}



/* private */



Collision::Collision( scene::ISceneManager* sceneManager )
: collisionPoint(VEC_3DF_NULL),
  collisionTriangle(core::triangle3df()),
  collisionNode(0),
  collisionDodgeVector(VEC_3DF_NULL),
  smgr_(sceneManager),
  selector_(0)
{
    if ( smgr_ == 0 )
    {
        Logfile::getInstance().emergencyExit(
                "SceneManager in [Collision] nicht mehr gefunden! Abbruch." );
    }
    colliman_ = smgr_->getSceneCollisionManager();
    walkableSelector_ = smgr_->createMetaTriangleSelector();
    collidableObjects_.clear();
    iter_ = collidableObjects_.begin();
}



Collision::~Collision()
{
    walkableSelector_->removeAllTriangleSelectors();
    walkableSelector_->drop();
    walkableSelector_ = 0;
    collidableObjects_.clear();
    iter_ = collidableObjects_.end();
}
