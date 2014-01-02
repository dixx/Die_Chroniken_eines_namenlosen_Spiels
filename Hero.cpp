#include "Hero.h"
#include "Collision.h"
#include "Constants.h"
#include "GenericHelperMethods.h"
#include "Ground.h"
#include "Logfile.h"
#include "ObjectManager.h"
#include "TimerManager.h"
#ifdef _DEBUG_MODE
#include "Debugwindow.h"
#endif



Hero::Hero( const core::stringc& objectData, scene::ISceneManager* sceneManager )
: BasicLifeform(objectData, sceneManager, true),
  smgr_(sceneManager),
  node_(0),
  currentPosition_(VEC_3DF_NULL),
  targetPosition_(VEC_3DF_NULL),
  lastPosition_(VEC_3DF_NULL),
  positionOffset_(VEC_3DF_NULL),
  scale_(core::vector3df( 0.025f, 0.025f, 0.025f )),
  rotation_(core::vector3df( 0.0f, -90.0f, 0.0f )),
  heroIsMoving_(false),
  heroWasMoving_(false),
  speed_(4.0f),
  movementDelta_(0.0f),
  traceTimer_(0),
  maxJumpHeight_(1.8f),
  collisionRadius_(0.0f)
{
    if ( smgr_ == 0 )
        Logfile::getInstance().emergencyExit(
                "SceneManager in [Hero] nicht mehr gefunden! Abbruch." );
    traceTimer_ = TimerManager::getInstance().createTimer( 0.8f );
}



Hero::~Hero()
{
    // Niemals droppen, wenn Objekt nicht durch "create" erzeugt wurde!
    TimerManager::getInstance().removeTimer( traceTimer_ );
}



void Hero::load()
{
    smgr_->getVideoDriver()->setTransform( video::ETS_WORLD, core::matrix4() );
    GenericHelperMethods::getInstance().validateFileExistence(
            "GFX/sydney.md2" );
    node_ = smgr_->addAnimatedMeshSceneNode(
            smgr_->getMesh( "GFX/sydney.md2" ),
            ObjectManager::getInstance().lifeformNodes,
            ID_HELD
    );
    node_->setMaterialTexture(
            0, smgr_->getVideoDriver()->getTexture( "GFX/sydney.bmp" ) );
    //this->node->addShadowVolumeSceneNode();  Durch Blob-Schatten ersetzen

    node_->setMaterialFlag( video::EMF_LIGHTING, true );
    node_->setMaterialFlag( video::EMF_NORMALIZE_NORMALS, true);
    node_->setMD2Animation( scene::EMAT_STAND );
    //node->setFrameLoop( 1, 40 );
    //node->setLoopMode( true );
    node_->setScale( scale_ );
    node_->setRotation( rotation_ );
    currentPosition_ = core::vector3df( 11.0f, 0.0f, 11.0f ); // 0 0
    Ground::getInstance().getHeightFromPosition( currentPosition_,
            maxJumpHeight_ );
    lastPosition_ = currentPosition_;
    targetPosition_ = currentPosition_;
    positionOffset_ = core::vector3df( 0.0f, 0.6f, 0.0f );
    update( 0.0f );
    calculateCollisionRadius();
}



void Hero::unload()
{
    traceTimer_->stop();
    node_->remove();
}



void Hero::update( const f32 frameDeltaTime )
{
    movementDelta_ = speed_ * frameDeltaTime;
    if ( heroIsMoving_ )
    {
        if ( targetPosition_.equals( currentPosition_, movementDelta_ ) )
        {
            stopMovement();
        }
        else
        {
            if ( !heroWasMoving_ )
            {
                node_->setMD2Animation( scene::EMAT_RUN );
                heroWasMoving_ = true;
            }
            calculateNextStep();
            node_->setPosition( currentPosition_ + nextStep_ + positionOffset_ );
            node_->updateAbsolutePosition();
            Collision& collision = Collision::getInstance();
            if ( collision.isObjectCollidingWithNodes( this ) )
            {
                nextStep_ = collision.collisionDodgeVector;
                node_->setPosition(
                        currentPosition_ + nextStep_ + positionOffset_ );
                node_->updateAbsolutePosition();
                if ( collision.isObjectCollidingWithNodes( this ) )
                    stopMovement();
                else
                    updateMovement();
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
    lastPosition_ = currentPosition_;
#ifdef _DEBUG_MODE
    Debugwindow& dw = Debugwindow::getInstance();
    dw.addLine( L"HeroIsMoving: ", heroIsMoving_ ? 1 : 0 );
    dw.addLine( L"HeroMovDelta: ", movementDelta_ );
    dw.addLine(
            L"HeroPos: ",
            node_->getAbsolutePosition().X,
            node_->getAbsolutePosition().Y,
            node_->getAbsolutePosition().Z
    );
    dw.addLine( L"HeroCurrentY: ", currentPosition_.Y );
    dw.addLine( L"HeroTargetY: ", targetPosition_.Y );
#endif
}



void Hero::moveTo( const core::vector3df target, bool isTriggered )
{
    if ( target.equals( currentPosition_, 0.5f ) ) // todo replace with some hero radius
        return;
    targetPosition_ = Ground::getInstance().getHeightFromPositionRanged(
            target, maxJumpHeight_ );
    if ( isTriggered )
    {
        if ( !traceTimer_->isRunning() )
            traceTimer_->start();
        heroIsMoving_ = true;
    }
    else
    {
        if ( traceTimer_->isFull() )
            targetPosition_ = currentPosition_;
        traceTimer_->stop();
    }
}



#ifdef _DEBUG_MODE
void Hero::toggleSpeed()
{
    speed_ = ( core::equals( speed_, 4.0f ) ) ? 200.0f : 4.0f;
}
#endif



/* private */



void Hero::calculateNextStep()
{
    nextStep_ = targetPosition_ - currentPosition_;
    nextStep_.setLength( movementDelta_ );
}



void Hero::calculateCollisionRadius()
{
//    core::vector3df dummy = node_->getTransformedBoundingBox().getExtent();
//    dummy.Y = 0.0f;
//    collisionRadius_ = dummy.getLength() * 0.5f;
    collisionRadius_ = 0.2f;
}



void Hero::updateMovement()
{
    currentPosition_ += nextStep_;
    core::vector3df direction( targetPosition_ - currentPosition_ );
    node_->setRotation(
            core::vector3df( direction.X, 0.0f, direction.Z )
            .getHorizontalAngle() + rotation_
    );
}



void Hero::stopMovement()
{
    heroIsMoving_ = false;
    if ( heroWasMoving_ )
    {
        node_->setMD2Animation( scene::EMAT_STAND );
        heroWasMoving_ = false;
        nextStep_ = VEC_3DF_NULL;
    }
}
