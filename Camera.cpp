#include "Camera.h"
#include "Configuration.h"
#include "Constants.h"
#include "Ground.h"
#include "Logfile.h"
#ifdef _DEBUG_MODE
#include "Debugwindow.h"
#endif



Camera& Camera::getInstance( scene::ISceneManager* sceneManager )
{
    static Camera _instance( sceneManager );
    return _instance;
}



void Camera::startZooming( const f32 direction )
{
    isZooming_ = true;
    zoomDir_ = direction;
}



void Camera::rotate( const f32 value )
{
    positionOffset_.rotateXZBy( speed_ * value );
}



void Camera::update( const f32 frameDeltaTime )
{
    if ( isZooming_ )
        changeZoom( frameDeltaTime );
    if ( lockNode_ )
        currentPosition_ = lockNode_->getPosition();
    currentTarget_ = currentPosition_ + targetOffset_;
    liftCameraToKeepTargetVisible();
    firstCameraNode_->setPosition( currentPosition_ + positionOffset_ );
    firstCameraNode_->setTarget( currentTarget_ );
#ifdef _DEBUG_MODE
    Debugwindow::getInstance().addLine(
            L"CamPos: ",
            firstCameraNode_->getAbsolutePosition().X,
            firstCameraNode_->getAbsolutePosition().Y,
            firstCameraNode_->getAbsolutePosition().Z
    );
    Debugwindow::getInstance().addLine( L"CamOffs.Y: ", positionOffset_.Y );
    Debugwindow::getInstance().addLine( L"CamZoom: ", isZooming_ ? 1 : 0 );
#endif
}



#ifdef _DEBUG_MODE
void Camera::toggleSpeed()
{
    speed_ = ( core::equals( speed_, 150.0f ) ) ? 300.0f : 150.0f;
}
core::vector3df& Camera::getCurrentPosition()
{
    return currentPosition_;
}
#endif



scene::ICameraSceneNode* Camera::getCurrentActive()
{
    return smgr_->getActiveCamera();
}



void Camera::lockToNode( scene::ISceneNode* node )
{
    lockNode_ = node;
}



/* private */



Camera::Camera( scene::ISceneManager* sceneManager )
: smgr_(sceneManager),
  lockNode_(0),
  targetOffset_(VEC_3DF_NULL),
  currentPosition_(VEC_3DF_NULL),
  speed_(150.0f),
  zoomingSpeed_(100.0f),
  zoomMin_(1.0f),
  zoomMax_(15.0f),
  isZooming_(false),
  zoomDir_(0),
  groundHeight_(0.0f),
  dummySum_(0.0f)
{
    if ( smgr_ == 0 )
    {
        Logfile::getInstance().emergencyExit(
                "SceneManager in [Camera] nicht mehr gefunden! Abbruch." );
    }
    desiredPositionOffsetHeight_ = zoomMax_;
    // dran denken, auch Ablaufsteuerung::checkInputForGame() zu ändern
    // wenn sich der speed ändert
    positionOffset_ = core::vector3df( -3.0f, zoomMax_, -3.0f );
    //this->currentPosition = map->GetStartPos() + Pos_offset;
    currentTarget_ = currentPosition_ + targetOffset_;
    firstCameraNode_ = smgr_->addCameraSceneNode(
            0, currentPosition_ + positionOffset_, currentTarget_, ID_KAMERA );
    // beim Anlegen schon geschehen:
    //this->smgr->setActiveCamera( this->firstCameraNode );
    firstCameraNode_->updateAbsolutePosition();
    firstCameraNode_->setName( "Kamera 1" );
    farValue_ = Configuration::getInstance().getFarValue();
    firstCameraNode_->setFarValue( farValue_ );
    firstCameraNode_->setNearValue( 0.1f );
    firstCameraNode_->setFOV( 1.25f );
    firstCameraNode_->setAspectRatio( 4.0f / 3.0f );
    firstCameraNode_->setInputReceiverEnabled( false );
    positionOffset_.rotateXZBy( -180.0f );
}



Camera::~Camera()
{
    // Niemals droppen, wenn Objekt nicht durch "create" erzeugt wurde!
}



void Camera::changeZoom( const f32 frameDeltaTime )
{
    dummySum_ = zoomingSpeed_ * frameDeltaTime;
    if ( zoomDir_ <= 0 )
    {
        // Rauszoomen == Draufsicht
        desiredPositionOffsetHeight_ = zoomMax_;
        if ( ( positionOffset_.Y + dummySum_ ) < zoomMax_ )
            positionOffset_.Y += dummySum_;
        else
            isZooming_ = false;
    }
    else
    {
        // Reinzoomen == Verfolgerperspektive
        desiredPositionOffsetHeight_ = zoomMin_;
        if ( ( positionOffset_.Y - dummySum_ ) > zoomMin_ )
            positionOffset_.Y -= dummySum_;
        else
            isZooming_ = false;
    }
}



void Camera::liftCameraToKeepTargetVisible()
{
//    this->groundHeight = Ground::getInstance().getHeightRanged(
//            this->currentPosition.X + this->positionOffset.X,
//            this->currentPosition.Z + this->positionOffset.Z
//    ) + 1.0f; // +1.0f damit Kamera nicht im Boden steckt
    groundHeight_ = Ground::getInstance().getHeightFromPositionRanged(
            currentPosition_ + positionOffset_
    ).Y + 1.0f; // +1.0f damit Kamera nicht im Boden steckt
    if ( isZooming_ )
        dummySum_ = currentPosition_.Y + positionOffset_.Y;
    else
        dummySum_ = currentPosition_.Y + desiredPositionOffsetHeight_;
    if ( dummySum_ < groundHeight_ )
        positionOffset_.Y = groundHeight_ - currentPosition_.Y;
    // todo bei Überschreiten von zoomMax das Offset näher an die Position
    //      heranrücken
}
