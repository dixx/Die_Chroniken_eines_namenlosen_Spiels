#include "Ground.h"
#include "Collision.h"
#include "Constants.h"
#include "GenericHelperMethods.h"
#include "Logfile.h"
#include "ObjectManager.h"
#include "ObjectParamsExtractor.h"
#include "Scripting.h"
#include "TimerManager.h"
#ifdef _DEBUG_MODE
#include "Debugwindow.h"
#endif



Ground& Ground::getInstance( irr::IrrlichtDevice* device )
{
    static Ground instance( device );
    return instance;
}



void Ground::load( const char* mapfilename )
{
    Logfile& logfile = Logfile::getInstance();
    irr::core::array<irr::core::stringc> tileList;
    irr::u32 position = 0;
    irr::s32 tileX = 0;
    irr::s32 tileZ = 0;

    // Kartenteile-Rohdaten laden
    GenericHelperMethods::getInstance().validateFileExistence( mapfilename );
    Scripting::getInstance().getObjectDataFromScript( mapfilename ).split( tileList, "\n" );

    // berechne Grid-Größe, prüfe Positionen auf Gültigkeit
    for ( register irr::u32 i = 0; i < tileList.size(); ++i )
    {
        ObjectParamsExtractor* extractor = new ObjectParamsExtractor( tileList[ i ] );
        if ( extractor->tryToExtractValue( "POSXZ", "x", 0 ) )
            tileX = irr::core::strtol10( extractor->getExtractedValue().c_str() );
        else
            exitWithLogEntry( "Fehlender X-Positionswert", mapfilename );
        if ( extractor->tryToExtractValue( "POSXZ", "x", 1 ) )
            tileZ = irr::core::strtol10( extractor->getExtractedValue().c_str() );
        else
            exitWithLogEntry( "Fehlender Z-Positionswert", mapfilename );
        if ( tileX < 0 || tileZ < 0 )
            exitWithLogEntry( "Negativer Positionswert", mapfilename );
        if ( tileX > 100 || tileZ > 100 )
            exitWithLogEntry( "Positionswert größer als 100", mapfilename );
        gridWidth_ = irr::core::max_( static_cast<irr::s32>( gridWidth_ ), tileX );
        gridDepth_ = irr::core::max_( static_cast<irr::s32>( gridDepth_ ), tileZ );
        delete extractor;
    }
    gridWidth_ += 1;
    gridDepth_ += 1;

    // initialisiere Grid
    for ( register irr::u32 i = 0; i <= gridWidth_ * gridDepth_; ++i )
        mapTiles_.push_back( 0 );

    // erstelle Grid mit Kartenteilen
#ifdef _DEBUG_MODE
irr::u32 now = device_->getTimer()->getRealTime();
#endif
    for ( register irr::u32 i = 0; i < tileList.size(); ++i )
    {
        MapTile* tile = new MapTile( tileList[ i ], smgr_, SECTORDIMENSION );
        if ( tile->getNode() == 0 )
        {
            delete tile;
            clearArrays();
            TimerManager::getInstance().removeTimer( updateTimer_ );
            logfile.emergencyExit( "Kartenteil konnte nicht erzeugt werden! Abbruch." );
        }
        position = tile->getX() + tile->getZ() * gridWidth_;
        maxHeight_ = irr::core::max_( maxHeight_, tile->getNode()->getTransformedBoundingBox().MaxEdge.Y );
        minHeight_ = irr::core::min_( minHeight_, tile->getNode()->getTransformedBoundingBox().MinEdge.Y );
        mapTiles_[ position ] = tile;
    }
#ifdef _DEBUG_MODE
    irr::core::stringw logText = L"";
    logText += tileList.size();
    logText += " Kartenteile in ";
    logText += device_->getTimer()->getRealTime() - now;
    logText += "ms erstellt.";
    logfile.writeLine( Logfile::DETAIL, logText.c_str() );
#endif
    tileList.clear();
    // einmal updaten, um Held setzen zu können
    updateTimer_->start();
    updateTimer_->tick( 1.0f );
    update();
    // auf kurz vor Knapp setzen, damit nach wenigen Frames die Visibility
    // aktualisiert wird (Workaround für "Held steht anfangs im Leeren")
    updateTimer_->tick( updateTimer_->getMaxValue() - 0.01f );
#ifdef _DEBUG_MODE
logfile.writeLine( Logfile::DEBUG, "TerrainMinY: ", minHeight_ );
logfile.writeLine( Logfile::DEBUG, "TerrainMaxY: ", maxHeight_ );
logfile.writeLine( Logfile::DEBUG, "Welt erstellt." );
#endif
}



void Ground::unload()
{
    clearArrays();
    gridWidth_ = 0;
    gridDepth_ = 0;
    minHeight_ = 100000.0f;
    maxHeight_ = 0.0f;
    updateTimer_->stop();
}



void Ground::update()
{
    if ( updateTimer_->isFull() )
    {
        irr::s32 sumX = 0;
        irr::s32 sumZ = 0;
        irr::s32 pos  = 0;
        irr::core::vector3df camPos = smgr_->getActiveCamera()->getAbsolutePosition();
        updateSectorX_ = irr::core::floor32( camPos.X / SECTORDIMENSION.Width );
        updateSectorZ_ = irr::core::floor32( camPos.Z / SECTORDIMENSION.Height );
        ObjectManager& objectManager = ObjectManager::getInstance();
#ifdef _DEBUG_MODE
        visibleNodeCount_ = 0;
#endif
        for ( register irr::s32 z = -2; z < 3; ++z )
        {
            sumZ = updateSectorZ_ + z;
            if ( sumZ < 0 || sumZ >= static_cast<irr::s32>( gridDepth_ ) )
                continue;
            for ( register irr::s32 x = -2; x < 3; ++x )
            {
                sumX = updateSectorX_ + x;
                if ( sumX < 0 || sumX >= static_cast<irr::s32>( gridWidth_ ) )
                    continue;
                pos = sumX + sumZ * gridWidth_;
                if ( mapTiles_[ pos ] == 0 )
                    continue;
                if ( x > -2 && x < 2 && z > -2 && z < 2 )
                {
                    if ( !mapTiles_[ pos ]->getNode()->isVisible() )
                        objectManager.addObjectToAreaOfView( mapTiles_[ pos ] );
#ifdef _DEBUG_MODE
                    ++visibleNodeCount_;
#endif
                }
                else
                {
                    if ( mapTiles_[ pos ]->getNode()->isVisible() )
                        objectManager.removeObjectFromAreaOfView( mapTiles_[ pos ] );
                }
            }
        }
        updateTimer_->restart();
    }
#ifdef _DEBUG_MODE
    Debugwindow::getInstance().addLine( "Ground::update1", L"sector: ", updateSectorX_, updateSectorZ_ );
    Debugwindow::getInstance().addLine( "Ground::update2", L"visSectors: ", visibleNodeCount_ );
#endif
}



irr::f32 Ground::getHeight( const irr::f32 x, const irr::f32 z )
{
    ray_ = irr::core::line3df( x, maxHeight_ + 1.0f, z, x, minHeight_ - 1.0f, z );
    if ( Collision::getInstance().isRayIntersectingWithWorld( ray_, ObjectManager::getInstance().walkableNodes ) )
        return Collision::getInstance().collisionPoint.Y;
    else
        return maxHeight_;
}



irr::core::vector3df& Ground::getHeightFromPosition( const irr::core::vector3df& position, irr::f32 heightOffset )
{
    ray_ = irr::core::line3df(
            position.X, position.Y + heightOffset, position.Z,
            position.X,         minHeight_ - 1.0f, position.Z
    );
    endPosition_ = irr::core::vector3df( position.X, maxHeight_, position.Z );
    if ( Collision::getInstance().isRayIntersectingWithWorld( ray_, ObjectManager::getInstance().walkableNodes ) )
        endPosition_ = Collision::getInstance().collisionPoint;
    return endPosition_;
}



irr::f32 Ground::getHeightRanged( const irr::f32 x, const irr::f32 z )
{
    ray_ = irr::core::line3df( x, maxHeight_ + 1.0f, z, x, minHeight_ - 1.0f, z );
//        if ( Collision::getInstance().isRayIntersectingWithWorld( this->ray,
//                ObjectManager::getInstance().walkableNodesInRange ) )
    if ( Collision::getInstance().isRayIntersectingWithWalkableNodesAroundHero( ray_ ) )
        return Collision::getInstance().collisionPoint.Y;
    else
        return maxHeight_;
}



irr::core::vector3df& Ground::getHeightFromPositionRanged( const irr::core::vector3df& position, irr::f32 heightOffset )
{
    ray_ = irr::core::line3df(
            position.X, position.Y + heightOffset, position.Z,
            position.X,         minHeight_ - 1.0f, position.Z
    );
    endPosition_ = irr::core::vector3df( position.X, maxHeight_, position.Z );
//    if ( Collision::getInstance().isRayIntersectingWithWorld( this->ray,
//            ObjectManager::getInstance().walkableNodesInRange ) )
    if ( Collision::getInstance().isRayIntersectingWithWalkableNodesAroundHero( ray_ ) )
        endPosition_ = Collision::getInstance().collisionPoint;
    return endPosition_;
}



#ifdef _DEBUG_MODE
void Ground::switchDebugMode()
{
    ( debugCounter_ == 4 ) ? debugCounter_ = 0 : ++debugCounter_;
    BufferCullMeshSceneNode* helperNode = 0;
    MapTile* helperTile = 0;
    for ( register irr::u32 z = 0; z < gridDepth_; ++z )
    {
        for ( register irr::u32 x = 0; x < gridWidth_; ++x )
        {
            helperTile = mapTiles_[ x + z * gridWidth_ ];
            if ( !helperTile ) continue;
            helperNode = helperTile->getNode();
            if ( !helperNode ) continue;
            if ( !helperNode->isVisible() ) continue;
            switch ( debugCounter_ )
            {
                case 0:
                    helperNode->setDebugDataVisible( 0 );
                    helperNode->setMaterialFlag( irr::video::EMF_WIREFRAME, false );
                    break;
                case 1:
                    helperNode->setDebugDataVisible( irr::scene::EDS_NORMALS );
                    break;
                case 2:
                    helperNode->setDebugDataVisible( 0 );
                    helperNode->setMaterialFlag( irr::video::EMF_WIREFRAME, true );
                    break;
                case 3:
                    helperNode->setDebugDataVisible( irr::scene::EDS_BBOX );
                    helperNode->setMaterialFlag( irr::video::EMF_WIREFRAME, false );
                    break;
                case 4:
                    helperNode->setDebugDataVisible( irr::scene::EDS_BBOX_BUFFERS );
                    helperNode->setMaterialFlag( irr::video::EMF_WIREFRAME, false );
                    break;
                default:
                    helperNode->setDebugDataVisible( 0 );
                    helperNode->setMaterialFlag( irr::video::EMF_WIREFRAME, false );
                    break;
            }
        }
    }
}
#endif



/* private */



Ground::Ground( irr::IrrlichtDevice* device )
: device_(device),
  SECTORDIMENSION(irr::core::dimension2df( 400.0f, 400.0f )),
  gridWidth_(0),
  gridDepth_(0),
  ray_(VEC_3DF_NULL, VEC_3DF_NULL),
  minHeight_(100000.0f),
  maxHeight_(0.0f),
  updateSectorX_(0),
  updateSectorZ_(0),
  endPosition_(VEC_3DF_NULL)
{
    if ( device_ == 0 )
        Logfile::getInstance().emergencyExit( "Entchen in [Ground] nicht mehr gefunden! Abbruch." );
    smgr_ = device_->getSceneManager();
    mapTiles_.clear();
    updateTimer_ = TimerManager::getInstance().createTimer( 0.9f );
#ifdef _DEBUG_MODE
    debugCounter_ = 0;
    visibleNodeCount_ = 0;
#endif
}



Ground::~Ground()
{
    // Niemals droppen, wenn Objekt nicht durch "create" erzeugt wurde!
    clearArrays();
    TimerManager::getInstance().removeTimer( updateTimer_ );
}



void Ground::clearArrays()
{
    if ( mapTiles_.size() > 0 )
    {
        for ( register irr::u32 i = 0; i < mapTiles_.size(); ++i )
        {
            if ( mapTiles_[ i ] )
            {
                delete mapTiles_[ i ];
                mapTiles_[ i ] = 0;
            }
        }
    }
    mapTiles_.clear();
}



void Ground::exitWithLogEntry( const irr::core::stringc& message, const char* affectedFile )
{
    clearArrays();
    TimerManager::getInstance().removeTimer( updateTimer_ );
    Logfile::getInstance().write( Logfile::INFO, message );
    Logfile::getInstance().write( Logfile::INFO, " in Datei ", affectedFile );
    Logfile::getInstance().emergencyExit( "! Abbruch." );
}
