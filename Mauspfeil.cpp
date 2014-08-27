#include "Mauspfeil.h"
#include "Constants.h"
#include "GenericHelperMethods.h"
#include "Logfile.h"
#ifdef _DEBUG_MODE
#include "Debugwindow.h"
#endif



Mauspfeil& Mauspfeil::getInstance( IrrlichtDevice* device )
{
    static Mauspfeil instance( device );
    return instance;
}



Mauspfeil::Pfeil Mauspfeil::getCurrentArrow() const
{
    return currentArrow_;
}



void Mauspfeil::setCurrentArrow( const Pfeil mauspfeil)
{
    currentArrow_ = ( mauspfeil < 0 || mauspfeil >= MAUSPFEIL_COUNT ) ? MAUSPFEIL_UNSICHTBAR : mauspfeil;
    actualImageNumber_ = startImageNumber_[ currentArrow_ ];
    setCurrentArrowInterFrameTime();
}



void Mauspfeil::draw()
{
    if ( device_->getTimer()->getRealTime() > sequenceTimer_ )
    {
        // Zeitgeber neu starten
        sequenceTimer_ = device_->getTimer()->getRealTime() + interFrameTime_;
        // nächstes Bild aus der Sequenz wählen
        if ( actualImageNumber_ == endImageNumber_[ currentArrow_ ] )
            actualImageNumber_ = startImageNumber_[ currentArrow_ ];
        else
            ++actualImageNumber_;
    }
    // Mauszeiger zeichnen
    device_->getVideoDriver()->draw2DImage(
            imageCatalog_, // Textur
            control_->getPosition() - hotSpot_, // Zielkoordinate ObenLinks
            imageCatalogActualPosition_[ actualImageNumber_ ],
            0, // Clipping-Rechteck, wird so gut wie nie gebraucht
            COL_WHITE, // Hintergrundfarbe, hier für Durchsichtigkeit==0
            true // Alpha-Kanal
    );
#ifdef _DEBUG_MODE
    Debugwindow::getInstance().addLine( "Mauspfeil::draw", L"mousePos = ", control_->getPosition().X, control_->getPosition().Y );
#endif



    //this->partikel->setPosition( this->control->getPosition() );
    // kaka! 2d to 3d
//    vector3df get3DCameraPlanePos( ICameraSceneNode* camera,
//            position2di position, dimension2di screenSize )
//    {
//       vector2df offPos(
//            ( screenSize.Width - position.X ) * 2.0f - 1.0f,
//            -( ( screenSize.Height - position.Y ) * 2.0f - 1.0f )
//       );
//       vector3df center = camera->getAbsolutePosition()
//            + camera->getAbsoluteTransformation().getRotationDegrees(
//            ).rotationToDirection();
//       vector3df dirX = (
//            camera->getViewFrustum()->getFarRightUp()-camera->getViewFrustum(
//            )->getFarLeftUp()
//       ).normalize();
//       vector3df dirY = (
//            camera->getViewFrustum()->getFarRightDown(
//            )-camera->getViewFrustum()->getFarRightUp()
//       ).normalize();
//       return center + dirX * offPos.X - dirY * offPos.Y;
//    }
//
//
//    // oder
//
//
//    vector2d<s32> mousePosition = m_cursor->getPosition();
//    line3d<f32> line = m_smgr->getSceneCollisionManager(
//            )->getRayFromScreenCoordinates(
//        mousePosition, m_smgr->getActiveCamera());
//    vector3df transformedMouse;
//    getIntersectionWithNearPlane(line, transformedMouse);
//
//    bool getIntersectionWithNearPlane(const core::line3d<f32> &line,
//            core::vector3d<f32> &outIntersection)
//    {
//       const scene::SViewFrustum *fr = m_smgr->getActiveCamera(
//            )->getViewFrustum();
//       core::plane3d<f32> plane = fr->planes[fr->VF_NEAR_PLANE];
//
//       return plane.getIntersectionWithLimitedLine(
//            line.start, line.end, outIntersection);
//    }

}



/* private */



Mauspfeil::Mauspfeil( IrrlichtDevice* device )
: device_(device),
  control_(0),
  imageCatalog_(0),
  imageCatalogRaster_(core::dimension2di( 3, 3 )),
  actualImageNumber_(0),
  interFrameTime_(0),
  imageSize_(core::recti( 0, 0, 60, 60 )),
  sequenceTimer_(0),
  currentArrow_(MAUSPFEIL_MISCHMASCH)
{
    if ( device_ == 0 )
        Logfile::getInstance().emergencyExit( "Entchen in [Mauspfeil] nicht mehr gefunden! Abbruch." );
    control_ = device_->getCursorControl();
    control_->setVisible( false );
    GenericHelperMethods::getInstance().validateFileExistence( "GFX/Mauszeiger.bmp" );
    imageCatalog_ = device->getVideoDriver()->getTexture( "GFX/Mauszeiger.bmp" );
    imageCatalog_->grab(); // to not accidently remove the texture elsewhere
    device_->getVideoDriver()->makeColorKeyTexture( imageCatalog_, COL_MAGICPINK );
    hotSpot_ = imageSize_.getCenter();
    clearArrays();
    // Vorberechnen der Positionen aller Einzelbilder innerhalb des
    // Imagekataloges, für schnelleren Zugriff
    for ( register s32 i = 0; i < imageCatalogRaster_.getArea(); ++i )
    {
        imageCatalogActualPosition_.push_back(
                core::recti(
                        ( i % imageCatalogRaster_.Width ) * imageSize_.getWidth(),
                        ( i / imageCatalogRaster_.Height ) * imageSize_.getHeight(),
                        ( i % imageCatalogRaster_.Width + 1 ) * imageSize_.getWidth(),
                        ( i / imageCatalogRaster_.Height + 1 ) * imageSize_.getHeight()
                )
        );
    }
#ifdef _DEBUG_MODE
    Logfile::getInstance().writeLine(
            Logfile::DEBUG,
            "Anzahl eingelesener Maus-Einzelbilder: ",
            imageCatalogActualPosition_.size()
    );
#endif
    // initialisieren der anderen Arrays
    for ( s32 i = 0; i < MAUSPFEIL_COUNT; ++i )
    {
        startImageNumber_.push_back( 0 );
        endImageNumber_.push_back( 0 );
        sequenceSpeed_.push_back( 0 );
    }

    // Start und Ende der Bildsequenz, bei Einzelbildern ist Start = Ende.
    // Bildnummern werden wie folgt ermittelt:
    //
    // Beispiel Bildaufteilung 4x3
    //
    //   0 |  1 |  2 |  3
    // ----+----+----+----
    //   4 |  5 |  6 |  7
    // ----+----+----+----
    //   8 |  9 | 10 | 11
    startImageNumber_[ MAUSPFEIL_UNSICHTBAR ] = 5;
    endImageNumber_[ MAUSPFEIL_UNSICHTBAR ]   = 5;
    startImageNumber_[ MAUSPFEIL_SELECT ] = 0;
    endImageNumber_[ MAUSPFEIL_SELECT ]   = 0;
    startImageNumber_[ MAUSPFEIL_GESPERRT ] = 1;
    endImageNumber_[ MAUSPFEIL_GESPERRT ]   = 1;
    startImageNumber_[ MAUSPFEIL_WARTE ] = 4;
    endImageNumber_[ MAUSPFEIL_WARTE ]   = 4;
    startImageNumber_[ MAUSPFEIL_MISCHMASCH ] = 0;
    endImageNumber_[ MAUSPFEIL_MISCHMASCH ]   = 3;

    actualImageNumber_ = startImageNumber_[ currentArrow_ ];
    // Bildwechsel-Framerate und Inter-Frame-Zeit setzen (FPS)
    // sequenceSpeed = 0 bedeutet kein Bildwechsel
    sequenceSpeed_[ MAUSPFEIL_UNSICHTBAR ] = 0;
    sequenceSpeed_[ MAUSPFEIL_SELECT ]     = 0;
    sequenceSpeed_[ MAUSPFEIL_GESPERRT ]   = 0;
    sequenceSpeed_[ MAUSPFEIL_WARTE ]      = 0;
    sequenceSpeed_[ MAUSPFEIL_MISCHMASCH ] = 30;
    setCurrentArrowInterFrameTime();
    // Zeitgeber starten
    sequenceTimer_ = device_->getTimer()->getTime() + interFrameTime_;
}



Mauspfeil::~Mauspfeil()
{
    clearArrays();
    imageCatalog_->drop();
}



void Mauspfeil::setCurrentArrowInterFrameTime()
{
    interFrameTime_ = ( sequenceSpeed_[ currentArrow_ ] == 0 ) ? 2147483647 : 1000 / sequenceSpeed_[ currentArrow_ ] ;
    // 2147483647 == Max unsigned Int31 ;)
}



void Mauspfeil::clearArrays()
{
    imageCatalogActualPosition_.clear();
    startImageNumber_.clear();
    endImageNumber_.clear();
    sequenceSpeed_.clear();
}
