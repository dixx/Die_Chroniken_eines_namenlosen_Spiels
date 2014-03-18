#include "BasicLifeform.h"
#include "Collision.h"
#include "Constants.h"
#include "GenericHelperMethods.h"
#include "Ground.h"
#include "Constants.h"
#include "Logfile.h"
#include "ObjectManager.h"



BasicLifeform::BasicLifeform(
        const core::stringc& objectData,
        scene::ISceneManager* smgr,
        bool isParent
)
: Basic3DObject(objectData, smgr, true),
  node_(0),
  isMoving_(false),
  wasMoving_(false),
  speed_(1.0f),
  movementDelta_(0.0f),
  currentPosition_(VEC_3DF_NULL),
  targetPosition_(VEC_3DF_NULL),
  positionOffset_(VEC_3DF_NULL),
  rotation_(VEC_3DF_NULL),
  nextStep_(VEC_3DF_NULL),
  maxJumpHeight_(0.0f)
{
    if ( smgr_ == 0 )
    {
        Logfile::getInstance().emergencyExit(
                "SceneManager in [BasicLifeform] nicht mehr gefunden! Abbruch."
        );
    }
    init();
    if ( !isParent )
        deleteExtractor();
}



BasicLifeform::~BasicLifeform()
{
    // Niemals droppen, wenn Objekt nicht durch "create" erzeugt wurde!
    Collision::getInstance().removeNodeFromWorld( node_ );
    node_->removeAll(); // removes children
    smgr_->getMeshCache()->removeMesh( node_->getMesh() );
    node_->remove();
}



void BasicLifeform::update( f32 frameDeltaTime )
{
    movementDelta_ = speed_ * frameDeltaTime;
    if ( isMoving_ )
    {
        if ( targetPosition_.equals( currentPosition_, movementDelta_ ) )
        {
            stopMovement();
        }
        else
        {
            if ( !wasMoving_ )
            {
                node_->setMD2Animation( scene::EMAT_RUN );
                wasMoving_ = true;
            }
            calculateNextStep();
            node_->setPosition( currentPosition_ + positionOffset_ + nextStep_ );
            node_->updateAbsolutePosition();
            Collision& collision = Collision::getInstance();
            if ( collision.isObjectCollidingWithNodes( this ) )
            {
                nextStep_ = collision.collisionDodgeVector;
                node_->setPosition(
                        currentPosition_ + positionOffset_ + nextStep_ );
                node_->updateAbsolutePosition();
                collision.isObjectCollidingWithNodes( this ) ?
                        stopMovement()
                        : updateMovement();
            }
            else
            {
                updateMovement();
            }
        }
    }
    // get height every time, in case of using an elevator
    currentPosition_ = Ground::getInstance().getHeightFromPositionRanged(
            currentPosition_, maxJumpHeight_ );
    node_->setPosition( currentPosition_ + positionOffset_ );
    node_->updateAbsolutePosition();
}



void BasicLifeform::moveTo( const core::vector3df target )
{
    targetPosition_ = Ground::getInstance().getHeightFromPositionRanged(
            target, maxJumpHeight_ );
}



scene::IAnimatedMeshSceneNode* BasicLifeform::getNode() const
{
    return node_;
}



f32 BasicLifeform::getCollisionRadius() const
{
    return collisionRadius_;
}



scene::ISceneNode* BasicLifeform::nodeInterface() const
{
    return static_cast<scene::ISceneNode*>(node_);
}



const core::vector3df& BasicLifeform::getNextStep() const
{
    return nextStep_;
}



core::stringc BasicLifeform::getObjectData()
{
    return "";
}



/* protected */



scene::IAnimatedMesh* BasicLifeform::loadMesh()
{
    scene::IAnimatedMesh* mesh = 0;
    if ( extractor_->tryToExtractValue( "MFILE" ) )
    {
        core::stringc meshFileName = extractor_->getExtractedValue();
        if ( meshFileName.size() == 0 )
        {
            createLogEntry( "Leerer Mesh-Dateiname" );
        }
        else
        {
            GenericHelperMethods::getInstance().validateFileExistence(
                    meshFileName );
            mesh = smgr_->getMesh( meshFileName );
        }
    }
    else
    {
        createLogEntry( "Kein Mesh-Dateiname" );
    }
    return mesh;
}



void BasicLifeform::calculateNextStep()
{
    nextStep_ = targetPosition_ - currentPosition_;
    nextStep_.setLength( movementDelta_ );
}



void BasicLifeform::calculateCollisionRadius()
{
    core::vector3df dummy = node_->getTransformedBoundingBox().getExtent();
    dummy.Y = 0.0f;
    collisionRadius_ = dummy.getLength() * 0.3f;
}



void BasicLifeform::updateMovement()
{
    currentPosition_ += nextStep_;
    core::vector3df direction( targetPosition_ - currentPosition_ );
    direction.Y = 0.0f;
    node_->setRotation( direction.getHorizontalAngle() + rotation_ );
}



void BasicLifeform::stopMovement()
{
    isMoving_ = false;
    if ( wasMoving_ )
    {
        node_->setMD2Animation( scene::EMAT_STAND );
        wasMoving_ = false;
        nextStep_ = VEC_3DF_NULL;
    }
}



/* private */



void BasicLifeform::init()
{
    smgr_->getVideoDriver()->setTransform( video::ETS_WORLD, core::matrix4() );
    node_ = smgr_->addAnimatedMeshSceneNode(
            loadMesh(),
            ObjectManager::getInstance().getBaseNodeByType( type_ ),
            ObjectManager::getInstance().getBaseIdByType( type_ )
    );
    currentPosition_ = loadPosition();
    targetPosition_ = currentPosition_;
    positionOffset_ = loadOffset();
    rotation_ = loadRotation();
    node_->setScale( loadScale() );
    node_->setName( name_ );
    node_->setRotation( rotation_ );
    node_->setPosition( currentPosition_ + positionOffset_ );
    node_->updateAbsolutePosition();
    node_->setMaterialTexture( 0, loadMainTexture() );
    for ( u32 i = 0; i < node_->getMaterialCount(); ++i )
        loadFilterAndEffects( node_->getMaterial( i ) );
    Collision::getInstance().addAnimatedMeshNodeToWorld( node_ );
    node_->setVisible( false );
    calculateCollisionRadius();
    //node_->addShadowVolumeSceneNode(); todo Durch Blob-Schatten ersetzen
}
