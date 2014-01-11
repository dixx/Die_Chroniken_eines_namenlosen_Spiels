#include "BasicHero.h"
#include "Ground.h"
#include "Logfile.h"
#include "TimerManager.h"



BasicHero::BasicHero(
        const core::stringc& heroData,
        scene::ISceneManager* smgr,
        bool isParent
)
: BasicLifeform(heroData, smgr, true)
{
    if ( smgr_ == 0 )
    {
        Logfile::getInstance().emergencyExit(
                "SceneManager in [BasicHero] nicht mehr gefunden! Abbruch."
        );
    }
    traceTimer_ = TimerManager::getInstance().createTimer( 0.8f );
    init();
    if ( !isParent )
        deleteExtractor();
}



BasicHero::~BasicHero()
{
    // Niemals droppen, wenn Objekt nicht durch "create" erzeugt wurde!
    TimerManager::getInstance().removeTimer( traceTimer_ );
}



void BasicHero::moveTo( const core::vector3df target, bool isTriggered )
{
    if ( target.equals( currentPosition_, 0.5f ) ) // todo replace with some hero radius
        return;
    targetPosition_ = Ground::getInstance().getHeightFromPositionRanged(
            target, maxJumpHeight_ );
    if ( isTriggered )
    {
        if ( !traceTimer_->isRunning() )
            traceTimer_->start();
        isMoving_ = true;
    }
    else
    {
        if ( traceTimer_->isFull() )
            targetPosition_ = currentPosition_;
        traceTimer_->stop();
    }
}



#ifdef _DEBUG_MODE
void BasicHero::toggleSpeed()
{
    speed_ = ( core::equals( speed_, 4.0f ) ) ? 200.0f : 4.0f;
}
#endif



/* private */



void BasicHero::init()
{
    speed_ = 4.0f;
    node_->setMaterialFlag( video::EMF_LIGHTING, true );
    node_->setMaterialFlag( video::EMF_NORMALIZE_NORMALS, true);
    node_->setMD2Animation( scene::EMAT_STAND );
    //node->setFrameLoop( 1, 40 );
    //node->setLoopMode( true );
}



//void Hero::calculateCollisionRadius()
//{
//    collisionRadius_ = 0.2f;
//}
