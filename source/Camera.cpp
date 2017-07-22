#include "Camera.h"
#include "Configuration.h"
#include "Constants.h"
#include "Ground.h"
#include "Logfile.h"
#ifdef _DEBUG_MODE
#include "Debugwindow.h"
#endif


// TODO rework to not be singleton
Camera& Camera::getInstance( irr::scene::ISceneManager* sceneManager )
{
    static Camera instance( sceneManager );
    return instance;
}



void Camera::startZoomingIn()
{
    isZooming_ = true;
    zoomDirection_ = ZOOM_IN;
}



void Camera::startZoomingOut()
{
    isZooming_ = true;
    zoomDirection_ = ZOOM_OUT;
}



void Camera::rotate( const irr::f32 value )
{
    positionOffset_.rotateXZBy( speed_ * value );
}



void Camera::update( const irr::f32 frameDeltaTime )
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
            "Camera::update1",
            L"CamPos: ",
            firstCameraNode_->getAbsolutePosition().X,
            firstCameraNode_->getAbsolutePosition().Y,
            firstCameraNode_->getAbsolutePosition().Z
    );
    Debugwindow::getInstance().addLine( "Camera::update2", L"CamOffs.Y: ", positionOffset_.Y );
    Debugwindow::getInstance().addLine( "Camera::update3", L"CamZoom: ", isZooming_ ? 1 : 0 );
#endif
}



#ifdef _DEBUG_MODE
void Camera::toggleSpeed()
{
    speed_ = ( irr::core::equals( speed_, 150.0f ) ) ? 300.0f : 150.0f;
}
irr::core::vector3df& Camera::getCurrentPosition()
{
    return currentPosition_;
}
#endif



void Camera::followNode( irr::scene::ISceneNode* node )
{
    lockNode_ = node;
}



/* private */



Camera::Camera( irr::scene::ISceneManager* sceneManager )
: smgr_(sceneManager),
  firstCameraNode_(0),
  lockNode_(0),
  currentTarget_(VEC_3DF_NULL),
  targetOffset_(VEC_3DF_NULL),
  currentPosition_(VEC_3DF_NULL),
  positionOffset_(VEC_3DF_NULL),
  speed_(150.0f),
  zoomingSpeed_(100.0f),
  desiredPositionOffsetHeight_(0.0f),
  zoomMin_(1.0f),
  zoomMax_(15.0f),
  isZooming_(false),
  zoomDirection_(ZOOM_OUT),
  groundHeight_(0.0f),
  dummySum_(0.0f)
{
    if ( smgr_ == 0 )
        Logfile::getInstance().emergencyExit( "SceneManager in [Camera] nicht mehr gefunden! Abbruch." );
    Configuration& config = Configuration::getInstance();
    desiredPositionOffsetHeight_ = zoomMax_;
    // dran denken, auch Ablaufsteuerung::checkInputForGame() zu ändern // TODO update comment!
    // wenn sich der speed ändert
    positionOffset_ = irr::core::vector3df( -3.0f, zoomMax_, -3.0f );
    //this->currentPosition = map->GetStartPos() + Pos_offset;
    currentTarget_ = currentPosition_ + targetOffset_;
    firstCameraNode_ = smgr_->addCameraSceneNode( 0, currentPosition_ + positionOffset_, currentTarget_, ID_KAMERA );
    // beim Anlegen schon geschehen:
    //this->smgr->setActiveCamera( this->firstCameraNode );
    firstCameraNode_->updateAbsolutePosition(); // ???
    firstCameraNode_->setName( "Kamera 1" );
    firstCameraNode_->setFarValue( config.getFarValue() );
    firstCameraNode_->setNearValue( 0.1f );
    firstCameraNode_->setFOV( 1.0f );
    firstCameraNode_->setAspectRatio(
            static_cast<irr::f32>( config.getScreenSize().Width ) / static_cast<irr::f32>( config.getScreenSize().Height ) );
    firstCameraNode_->setInputReceiverEnabled( false );
    positionOffset_.rotateXZBy( -180.0f ); // ???
}



Camera::~Camera()
{
    // Niemals droppen, wenn Objekt nicht durch "create" erzeugt wurde!
}



void Camera::changeZoom( const irr::f32 frameDeltaTime )
{
    dummySum_ = zoomingSpeed_ * frameDeltaTime;
    if ( zoomDirection_ == ZOOM_OUT )
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
    groundHeight_ = Ground::getInstance().getHeightFromPositionRanged( currentPosition_ + positionOffset_ ).Y + 1.0f;
            // +1.0f damit Kamera nicht im Boden steckt
    if ( isZooming_ )
        dummySum_ = currentPosition_.Y + positionOffset_.Y;
    else
        dummySum_ = currentPosition_.Y + desiredPositionOffsetHeight_;
    if ( dummySum_ < groundHeight_ )
        positionOffset_.Y = groundHeight_ - currentPosition_.Y;
    // todo bei Überschreiten von zoomMax das Offset näher an die Position
    //      heranrücken
}
