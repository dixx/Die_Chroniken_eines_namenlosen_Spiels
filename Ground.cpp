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



Ground& Ground::getInstance( IrrlichtDevice* device )
{
    static Ground _instance( device );
    return _instance;
}



void Ground::load( const char* mapfilename )
{
    core::array<core::stringc> tileList;
    u32 position = 0;
    s32 tileX = 0;
    s32 tileZ = 0;

    // Kartenteile-Rohdaten laden
    GenericHelperMethods::getInstance().validateFileExistence( mapfilename );
    Scripting::getInstance().getObjectDataFromScript(
            mapfilename ).split( tileList, "\n" );

    // berechne Grid-Größe, prüfe Positionen auf Gültigkeit
    for ( register u32 i = 0; i < tileList.size(); ++i )
    {
        ObjectParamsExtractor* extractor = new ObjectParamsExtractor(
                tileList[ i ] );
        if ( extractor->tryToExtractValue( "POSXZ", "x", 0 ) )
            tileX = core::strtol10( extractor->getExtractedValue().c_str() );
        else
            exitWithLogEntry( "Fehlender X-Positionswert", mapfilename );
        if ( extractor->tryToExtractValue( "POSXZ", "x", 1 ) )
            tileZ = core::strtol10( extractor->getExtractedValue().c_str() );
        else
            exitWithLogEntry( "Fehlender Z-Positionswert", mapfilename );
        if ( tileX < 0 || tileZ < 0 )
            exitWithLogEntry( "Negativer Positionswert", mapfilename );
        if ( tileX > 100 || tileZ > 100 )
            exitWithLogEntry( "Positionswert größer als 100", mapfilename );
        gridWidth_ = core::max_( static_cast<s32>( gridWidth_ ), tileX );
        gridDepth_ = core::max_( static_cast<s32>( gridDepth_ ), tileZ );
        delete extractor;
    }
    gridWidth_ += 1;
    gridDepth_ += 1;

    // initialisiere Grid
    for ( register u32 i = 0; i <= gridWidth_ * gridDepth_; ++i )
        mapTiles_.push_back( 0 );

    // erstelle Grid mit Kartenteilen
#ifdef _DEBUG_MODE
u32 now = device_->getTimer()->getRealTime();
#endif
    for ( register u32 i = 0; i < tileList.size(); ++i )
    {
        MapTile* tile = new MapTile( tileList[ i ], smgr_, SECTORDIMENSION );
        if ( tile->getNode() == 0 )
        {
            delete tile;
            clearArrays();
            TimerManager::getInstance().removeTimer( updateTimer_ );
            Logfile::getInstance().emergencyExit(
                    "Kartenteil konnte nicht erzeugt werden! Abbruch." );
        }
        position = tile->getX() + tile->getZ() * gridWidth_;
        maxHeight_ = core::max_(
                maxHeight_,
                tile->getNode()->getTransformedBoundingBox().MaxEdge.Y
        );
        minHeight_ = core::min_(
                minHeight_,
                tile->getNode()->getTransformedBoundingBox().MinEdge.Y
        );
        mapTiles_[ position ] = tile;
    }
#ifdef _DEBUG_MODE
    core::stringw logText = L"";
    logText += tileList.size();
    logText += " Kartenteile in ";
    logText += device_->getTimer()->getRealTime() - now;
    logText += "ms erstellt.";
    Logfile::getInstance().writeLine( Logfile::DETAIL, logText.c_str() );
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
Logfile::getInstance().writeLine( Logfile::DEBUG, "TerrainMinY: ", minHeight_ );
Logfile::getInstance().writeLine( Logfile::DEBUG, "TerrainMaxY: ", maxHeight_ );
Logfile::getInstance().writeLine( Logfile::DEBUG, "Welt erstellt." );
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
        s32 sumX = 0;
        s32 sumZ = 0;
        s32 pos  = 0;
        core::vector3df camPos =
                smgr_->getActiveCamera()->getAbsolutePosition();
        updateSectorX_ = core::floor32( camPos.X / SECTORDIMENSION.Width );
        updateSectorZ_ = core::floor32( camPos.Z / SECTORDIMENSION.Height );
        ObjectManager& objectManager = ObjectManager::getInstance();
#ifdef _DEBUG_MODE
        visibleNodeCount_ = 0;
#endif
        for ( register s32 z = -2; z < 3; ++z )
        {
            sumZ = updateSectorZ_ + z;
            if ( sumZ < 0 || sumZ >= static_cast<s32>( gridDepth_ ) )
                continue;
            for ( register s32 x = -2; x < 3; ++x )
            {
                sumX = updateSectorX_ + x;
                if ( sumX < 0 || sumX >= static_cast<s32>( gridWidth_ ) )
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
                        objectManager.removeObjectFromAreaOfView(
                                mapTiles_[ pos ] );
                }
            }
        }
        updateTimer_->restart();
    }
#ifdef _DEBUG_MODE
    Debugwindow::getInstance().addLine(
            L"sector: ", updateSectorX_, updateSectorZ_ );
    Debugwindow::getInstance().addLine( L"visSectors: ", visibleNodeCount_ );
#endif
}



f32 Ground::getHeight( const f32 x, const f32 z )
{
    ray_ = core::line3df( x, maxHeight_ + 1.0f, z, x, minHeight_ - 1.0f, z );
    if ( Collision::getInstance().isRayIntersectingWithWorld( ray_,
            ObjectManager::getInstance().walkableNodes ) )
    {
        return Collision::getInstance().collisionPoint.Y;
    }
    else
    {
        return maxHeight_;
    }
}



core::vector3df& Ground::getHeightFromPosition(
        const core::vector3df& position, f32 heightOffset )
{
    ray_ = core::line3df(
            position.X, position.Y + heightOffset, position.Z,
            position.X,         minHeight_ - 1.0f, position.Z
    );
    endPosition_ = core::vector3df( position.X, maxHeight_, position.Z );
    if ( Collision::getInstance().isRayIntersectingWithWorld( ray_,
            ObjectManager::getInstance().walkableNodes ) )
    {
        endPosition_ = Collision::getInstance().collisionPoint;
    }
    return endPosition_;
}



f32 Ground::getHeightRanged( const f32 x, const f32 z )
{
    ray_ = core::line3df( x, maxHeight_ + 1.0f, z, x, minHeight_ - 1.0f, z );
    if ( Collision::getInstance().isRayIntersectingWithWalkableNodesAroundHero(
            ray_ ) )
//        if ( Collision::getInstance().isRayIntersectingWithWorld( this->ray,
//                ObjectManager::getInstance().walkableNodesInRange ) )
    {
        return Collision::getInstance().collisionPoint.Y;
    }
    else
    {
        return maxHeight_;
    }
}



core::vector3df& Ground::getHeightFromPositionRanged(
        const core::vector3df& position, f32 heightOffset )
{
    ray_ = core::line3df(
            position.X, position.Y + heightOffset, position.Z,
            position.X,         minHeight_ - 1.0f, position.Z
    );
    endPosition_ = core::vector3df( position.X, maxHeight_, position.Z );
    if ( Collision::getInstance().isRayIntersectingWithWalkableNodesAroundHero(
            ray_ ) )
//    if ( Collision::getInstance().isRayIntersectingWithWorld( this->ray,
//            ObjectManager::getInstance().walkableNodesInRange ) )
    {
        endPosition_ = Collision::getInstance().collisionPoint;
    }
    return endPosition_;
}



#ifdef _DEBUG_MODE
void Ground::switchDebugMode()
{
    ( debugCounter_ == 4 ) ? debugCounter_ = 0 : ++debugCounter_;
    BufferCullMeshSceneNode* helperNode = 0;
    MapTile* helperTile = 0;
    for ( register u32 z = 0; z < gridDepth_; ++z )
    {
        for ( register u32 x = 0; x < gridWidth_; ++x )
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
                    helperNode->setMaterialFlag( video::EMF_WIREFRAME, false );
                    break;
                case 1:
                    helperNode->setDebugDataVisible( scene::EDS_NORMALS );
                    break;
                case 2:
                    helperNode->setDebugDataVisible( 0 );
                    helperNode->setMaterialFlag( video::EMF_WIREFRAME, true );
                    break;
                case 3:
                    helperNode->setDebugDataVisible( scene::EDS_BBOX );
                    helperNode->setMaterialFlag( video::EMF_WIREFRAME, false );
                    break;
                case 4:
                    helperNode->setDebugDataVisible( scene::EDS_BBOX_BUFFERS );
                    helperNode->setMaterialFlag( video::EMF_WIREFRAME, false );
                    break;
                default:
                    helperNode->setDebugDataVisible( 0 );
                    helperNode->setMaterialFlag( video::EMF_WIREFRAME, false );
                    break;
            }
        }
    }
}
#endif



/* private */



Ground::Ground( IrrlichtDevice* device )
: device_(device),
  SECTORDIMENSION(core::dimension2df( 400.0f, 400.0f )),
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
    {
        Logfile::getInstance().emergencyExit(
                "Entchen in [Ground] nicht mehr gefunden! Abbruch." );
    }
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
    Collision& colliMan = Collision::getInstance();
    if ( mapTiles_.size() > 0 )
    {
        for ( register u32 i = 0; i < mapTiles_.size(); ++i )
        {
            if ( mapTiles_[ i ] )
            {
                colliMan.removeObjectFromRangedDetection( mapTiles_[ i ] );
                colliMan.removeNodeFromWorld( mapTiles_[ i ]->nodeInterface() );
                delete mapTiles_[ i ];
                mapTiles_[ i ] = 0;
            }
        }
    }
    mapTiles_.clear();
}



void Ground::exitWithLogEntry( const core::stringc& message,
        const char* affectedFile )
{
    clearArrays();
    TimerManager::getInstance().removeTimer( updateTimer_ );
    Logfile::getInstance().write( Logfile::INFO, message );
    Logfile::getInstance().write( Logfile::INFO, " in Datei ", affectedFile );
    Logfile::getInstance().emergencyExit( "! Abbruch." );
}
