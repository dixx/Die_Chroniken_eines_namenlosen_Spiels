#include "Collision.h"
#include "Constants.h"
#ifdef _DEBUG_MODE
#include "DebugShapesManager.h"
#include "Debugwindow.h"
#endif
#include "Eventreceiver.h"
#include "Logfile.h"
#include "ObjectManager.h"
#include "Zufall.h"



Collision& Collision::getInstance( scene::ISceneManager* sceneManager )
{
    static Collision instance( sceneManager );
    return instance;
}



void Collision::addStaticMeshNodeToWorld( scene::IMeshSceneNode* node )
{
    // todo minimalPolysPerNode anpassen
    // DEPRECATED since 1.7.2
    //this->selector = smgr->createOctTreeTriangleSelector(
    selector_ = smgr_->createOctreeTriangleSelector( node->getMesh(), node, 900 );
    node->setTriangleSelector( selector_ );
    selector_ = 0;
}



void Collision::addAnimatedMeshNodeToWorld( scene::IAnimatedMeshSceneNode* node )
{
    selector_ = smgr_->createTriangleSelector( node );
    node->setTriangleSelector( selector_ );
    selector_ = 0;
}



void Collision::removeNodeFromWorld( scene::ISceneNode* node )
{
    selector_ = node->getTriangleSelector();
    if ( selector_ )
    {
        node->setTriangleSelector( 0 );
        selector_->drop();
    }
}



void Collision::addObjectToRangedDetection( Basic3DObject* object )
{
    if ( object->nodeInterface()->getID() & ID_FLAG_BEGEHBAR )
        walkableSelector_->addTriangleSelector( object->nodeInterface()->getTriangleSelector() );
    if ( object->nodeInterface()->getID() & ID_FLAG_KOLLIDIERBAR )
        collidableObjects_.push_back( object );
}



void Collision::removeObjectFromRangedDetection( Basic3DObject* object )
{
    if ( object->nodeInterface()->getID() & ID_FLAG_BEGEHBAR )
        walkableSelector_->removeTriangleSelector( object->nodeInterface()->getTriangleSelector() );
    if ( object->nodeInterface()->getID() & ID_FLAG_KOLLIDIERBAR )
    {
        for( iter_ = collidableObjects_.begin(); iter_ != collidableObjects_.end(); ++iter_ )
        {
            if( *iter_ == object )
            {
                collidableObjects_.erase( iter_ );
                break;
            }
        }
    }
}



bool Collision::isRayIntersectingWithWorld( const core::line3df& ray, scene::ISceneNode* rootNode )
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



bool Collision::isRayIntersectingWithWalkableNodesAroundHero( const core::line3df& ray )
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



bool Collision::isObjectCollidingWithNodes( Basic3DObject* object )
{
    // TODO refactor!
    bool isCollision = false;
    scene::ISceneNode* objectNode = object->nodeInterface();
    f32 objectRadius = object->getCollisionRadius();
    const core::vector3df& objectCenter = objectNode->getAbsolutePosition();
    core::aabbox3df objectBB = object->getMaxBoundingBox();
#ifdef _DEBUG_MODE
    DebugShapesManager::getInstance().createEllipsoid( objectCenter, objectBB.MaxEdge - objectCenter );
#endif
    Basic3DObject* obstacle = 0;
    scene::ISceneNode* obstacleNode = 0;
    f32 obstacleRadius = 0.0f;
    f32 minDistance = 0.0f;
    core::vector3df distance;
    for( iter_ = collidableObjects_.begin(); iter_ != collidableObjects_.end(); ++iter_ )
    {
        obstacle = *iter_;
        obstacleNode = obstacle->nodeInterface();
        if ( obstacleNode == objectNode ) // this works because of "intuitive pointer equality"
            continue;
        obstacleRadius = obstacle->getCollisionRadius();
        if ( obstacleRadius > core::ROUNDING_ERROR_f32 ) // Lebewesen?
        {
            minDistance = objectRadius + obstacleRadius;
            distance = obstacleNode->getAbsolutePosition() - objectCenter;
            distance.Y = 0.0f;
            if ( ( distance.getLength() - minDistance ) < 0.0f )
            {
                isCollision = true;
                collisionDodgeVector = distance
                        - core::vector3df( distance ).setLength( minDistance + 0.01f )
                        + object->getNextStep();
            }
        }
        else
        {
            if ( obstacleNode->getTransformedBoundingBox().intersectsWithBox( objectBB ) )
            {
                bool _;
                collisionNode = 0;
                colliman_->getCollisionResultPosition(
                        obstacleNode->getTriangleSelector(),
                        objectCenter, // ellipsoidPosition
                        objectBB.MaxEdge - objectCenter, // ellipsoidRadius
                        object->getNextStep(), // ellipsoidDirectionAndSpeed
                        collisionTriangle,
                        collisionPoint,
                        _, // isFalling
                        collisionNode
                );
                if ( collisionNode )
                {
                    isCollision = true;
                    collisionDodgeVector = -object->getNextStep(); // reset movement
                    // TODO make object either halt or slide along
                }
            }
        }
        if ( isCollision )
        {
#ifdef _DEBUG_MODE
            Debugwindow& dw = Debugwindow::getInstance();
            dw.addLine( "Collision::isObjectCollidingWithNodes1", L"collision with: ", obstacle->getName() );
            dw.addLine( "Collision::isObjectCollidingWithNodes2", L"ObjectCollisionRadius: ", objectRadius );
            dw.addLine( "Collision::isObjectCollidingWithNodes3", L"ObstacleCollisionRadius: ", obstacle->getCollisionRadius() );
            dw.addLine(
                    "Collision::isObjectCollidingWithNodes4", L"ellipsoidRadien: ",
                    objectBB.MaxEdge.X - objectCenter.X,
                    objectBB.MaxEdge.Y - objectCenter.Y,
                    objectBB.MaxEdge.Z - objectCenter.Z
            );
#endif
            return true;
        }
    }
    return false;
}



bool Collision::isMouseIntersectingWithWorld()
{
    return isRayIntersectingWithWorld(
            colliman_->getRayFromScreenCoordinates(
                    core::position2di(
                            Eventreceiver::getInstance().getMouseX(),
                            Eventreceiver::getInstance().getMouseY()
                    ),
                    smgr_->getActiveCamera()
            ),
            ObjectManager::getInstance().nodesRespondingToMouse
    );
}



void Collision::clearRemainingSelectors()
{
    walkableSelector_->removeAllTriangleSelectors();
}



#ifdef _DEBUG_MODE
u32 Collision::loadedSelectors()
{
    return walkableSelector_->getSelectorCount() + collidableObjects_.size();
}
#endif


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
        Logfile::getInstance().emergencyExit( "SceneManager in [Collision] nicht mehr gefunden! Abbruch." );
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
