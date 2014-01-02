#include "ObjectManager.h"
#include "Collision.h"
#include "Constants.h"
#include "GenericHelperMethods.h"
#include "Ground.h"
#include "Logfile.h"
#include "Scripting.h"
#include "TimerManager.h"
#ifdef _DEBUG_MODE
    #include "Debugwindow.h"
#endif



ObjectManager& ObjectManager::getInstance( IrrlichtDevice* device )
{
    static ObjectManager _instance( device );
    return _instance;
}



void ObjectManager::loadSolids( const char* solidsFilename )
{
    core::array<core::stringc> objectsDataList;

    GenericHelperMethods::getInstance().validateFileExistence( solidsFilename );
    Scripting::getInstance().getObjectDataFromScript(
            solidsFilename ).split( objectsDataList, "\n" );

#ifdef _DEBUG_MODE
u32 now = device_->getTimer()->getRealTime();
#endif
    for ( register u32 i = 0; i < objectsDataList.size(); ++i )
    {
        BasicStaticObject* object = new BasicStaticObject(
                objectsDataList[ i ], smgr_ );
        if ( object->getNode() == 0 )
        {
            delete object;
            clearArrays();
            TimerManager::getInstance().removeTimer( updateTimer_ );
            Logfile::getInstance().emergencyExit(
                    "Statisches Objekt konnte nicht erzeugt werden! Abbruch." );
        }
        // Auf Boden positionieren
        core::vector3df pos = object->getNode()->getPosition();
        pos.Y = Ground::getInstance().getHeight( pos.X, pos.Z );
        object->getNode()->setPosition( pos );
        staticObjects_.push_back( object );
    }
#ifdef _DEBUG_MODE
Logfile::getInstance().write( Logfile::DEBUG, "", staticObjects_.size() );
Logfile::getInstance().write(
    Logfile::DETAIL,
    " statische Objekte in ",
    device_->getTimer()->getRealTime() - now
);
Logfile::getInstance().writeLine( Logfile::DETAIL, "ms erstellt." );
#endif
    objectsDataList.clear();
    updateTimer_->start();
}



void ObjectManager::loadNPCs( const char* npcsFilename )
{
    core::array<core::stringc> objectsDataList;

    GenericHelperMethods::getInstance().validateFileExistence( npcsFilename );
    Scripting::getInstance().getObjectDataFromScript(
            npcsFilename ).split( objectsDataList, "\n" );

#ifdef _DEBUG_MODE
u32 now = device_->getTimer()->getRealTime();
#endif
    for ( register u32 i = 0; i < objectsDataList.size(); ++i )
    {
        BasicLifeform* npc = new BasicLifeform( objectsDataList[ i ], smgr_ );
        if ( npc->getNode() == 0 )
        {
            delete npc;
            clearArrays();
            TimerManager::getInstance().removeTimer( updateTimer_ );
            Logfile::getInstance().emergencyExit(
                    "NPC konnte nicht erzeugt werden! Abbruch." );
        }
        // Auf Boden positionieren
        core::vector3df pos = npc->getNode()->getPosition();
        pos.Y = Ground::getInstance().getHeight( pos.X, pos.Z );
        npc->getNode()->setPosition( pos );
        npcs_.push_back( npc );
    }
#ifdef _DEBUG_MODE
Logfile::getInstance().write( Logfile::DEBUG, "", npcs_.size() );
Logfile::getInstance().write(
    Logfile::DETAIL,
    " NPCs in ",
    device_->getTimer()->getRealTime() - now
);
Logfile::getInstance().writeLine( Logfile::DETAIL, "ms erstellt." );
#endif
    objectsDataList.clear();
    updateTimer_->start();
}



void ObjectManager::unload()
{
    clearArrays();
    updateTimer_->stop();
}



void ObjectManager::update( const f32 frameDeltaTime )
{
    if ( updateTimer_->isFull() )
    {
        scene::ISceneNode* node = 0;
        core::vector3df camPos = smgr_->getActiveCamera()->getAbsolutePosition();
        f32 farValueSQ = smgr_->getActiveCamera()->getFarValue();
        farValueSQ *= farValueSQ;
#ifdef _DEBUG_MODE
        visibleNodeCount_ = 0;
#endif
        for( u32 i = 0; i < staticObjects_.size(); ++i )
        {
            node = staticObjects_[ i ]->getNode();
            if ( ( node->getID() & ID_WELT ) == ID_BODEN )
                continue;  // Boden wird in Ground::update() aktualisiert
            if ( node->getAbsolutePosition().getDistanceFromSQ( camPos )
                    < farValueSQ )
            {
                if ( !node->isVisible() )
                    addObjectToAreaOfView( staticObjects_[ i ] );
#ifdef _DEBUG_MODE
                visibleNodeCount_++;
#endif
            }
            else
            {
                if ( node->isVisible() )
                    removeObjectFromAreaOfView( staticObjects_[ i ] );
            }
        }
        for( u32 i = 0; i < npcs_.size(); ++i )
        {
            node = npcs_[ i ]->getNode();
            if ( node->getAbsolutePosition().getDistanceFromSQ( camPos )
                    < farValueSQ )
            {
                if ( !node->isVisible() )
                    addObjectToAreaOfView( npcs_[ i ] );
#ifdef _DEBUG_MODE
                visibleNodeCount_++;
#endif
            }
            else
            {
                if ( node->isVisible() )
                    removeObjectFromAreaOfView( npcs_[ i ] );
            }
        }
        updateTimer_->restart();
    }
#ifdef _DEBUG_MODE
    Debugwindow::getInstance().addLine( L"visibleNodes: ", visibleNodeCount_ );
#endif
    for( u32 i = 0; i < npcs_.size(); ++i )
    {
        npcs_[ i ]->update( frameDeltaTime );
    }
}



scene::ISceneNode* ObjectManager::getBaseNodeByType( const core::stringc& type )
{
    scene::ISceneNode* node = 0;
    if ( type.equals_ignore_case( "mauspfeilreaktiv" ) )
        node = nodesRespondingToMouse;
    else if ( type.equals_ignore_case( "begehbar" ) )
        node = walkableNodes;
    else if ( type.equals_ignore_case( "leiche" ) )
        node = corpseNodes;
    else if ( type.equals_ignore_case( "lebewesen" ) )
        node = lifeformNodes;
    else if ( type.equals_ignore_case( "inventar" ) )
        node = inventoryNodes;
    else if ( type.equals_ignore_case( "interaktiv" ) )
        node = interactiveNodes;
    else if ( type.equals_ignore_case( "hindernis" ) )
        node = obstacleNodes;
    else if ( type.equals_ignore_case( "wetter" ) )
        node = weatherNodes;
    else if ( type.equals_ignore_case( "geschoss" ) )
        node = bulletNodes;
    else
        node = decorativeNodes;
    return node;
}



u32 ObjectManager::getBaseIdByType( const core::stringc& type )
{
    return getBaseNodeByType( type )->getID();
}



// ersetzen.
void ObjectManager::addObjectToAreaOfView(Basic3DObject* object)
{
    object->nodeInterface()->setVisible( true );
    Collision::getInstance().addObjectToRangedDetection( object );
}



// ersetzen.
void ObjectManager::removeObjectFromAreaOfView(Basic3DObject* object)
{
    object->nodeInterface()->setVisible( false );
    Collision::getInstance().removeObjectFromRangedDetection( object );
}



#ifdef _DEBUG_MODE
void ObjectManager::switchStaticsDebugMode()
{
    ( debugCounter_ == 4 ) ? debugCounter_ = 0 : debugCounter_++;
    BufferCullMeshSceneNode* helperNode = 0;
    BasicStaticObject* helperObject = 0;
    for ( register u32 i = 0; i < staticObjects_.size(); ++i )
    {
        helperObject = staticObjects_[ i ];
        if ( !helperObject )
            continue;
        helperNode = helperObject->getNode();
        if ( !helperNode )
            continue;
        if ( !helperNode->isVisible() )
            continue;
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
void ObjectManager::switchNPCsDebugMode()
{
    ( debugCounter_ == 4 ) ? debugCounter_ = 0 : debugCounter_++;
    scene::IAnimatedMeshSceneNode* helperNode = 0;
    BasicLifeform* helperObject = 0;
    for ( register u32 i = 0; i < npcs_.size(); ++i )
    {
        helperObject = npcs_[ i ];
        if ( !helperObject )
            continue;
        helperNode = helperObject->getNode();
        if ( !helperNode )
            continue;
        if ( !helperNode->isVisible() )
            continue;
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
#endif



/* private */



ObjectManager::ObjectManager( IrrlichtDevice* device )
: device_(device),
  smgr_(0),
  staticObjects_(0),
  npcs_(0),
  updateTimer_(0)
#ifdef _DEBUG_MODE
  ,visibleNodeCount_(0)
  ,debugCounter_(0)
#endif

{
    if ( device_ == 0 )
    {
        Logfile::getInstance().emergencyExit(
                "Entchen in [ObjectManager] nicht mehr gefunden! Abbruch." );
    }
    smgr_ = device_->getSceneManager();
	worldNode = smgr_->addEmptySceneNode( 0, ID_WELT );
	worldNode->setName( "worldNode" );
    nodesRespondingToMouse = smgr_->addEmptySceneNode(
            worldNode,
            ID_MAUSPFEILREAKTIV + ID_FLAG_MAUSPFEILREAKTIV
    );
    nodesRespondingToMouse->setName( "nodesRespondingToMouse" );
    walkableNodes = smgr_->addEmptySceneNode(
            nodesRespondingToMouse,
            ID_BEGEHBAR + ID_FLAG_BEGEHBAR + ID_FLAG_MAUSPFEILREAKTIV
    );
    walkableNodes->setName( "walkableNodes" );
    walkableNodesInRange = smgr_->addEmptySceneNode(
            walkableNodes,
            walkableNodes->getID()
    );
    walkableNodesInRange->setName( "walkableNodesInRange" );
    corpseNodes = smgr_->addEmptySceneNode(
            nodesRespondingToMouse,
            ID_LEICHEN + ID_FLAG_MAUSPFEILREAKTIV
    );
    corpseNodes->setName( "corpseNodes" );
    lifeformNodes = smgr_->addEmptySceneNode(
            nodesRespondingToMouse,
            ID_LEBEWESEN + ID_FLAG_MAUSPFEILREAKTIV + ID_FLAG_KOLLIDIERBAR
    );
    lifeformNodes->setName( "lifeformNodes" );
    inventoryNodes = smgr_->addEmptySceneNode(
            nodesRespondingToMouse,
            ID_INVENTAR + ID_FLAG_MAUSPFEILREAKTIV
    );
    inventoryNodes->setName( "inventoryNodes" );
    interactiveNodes = smgr_->addEmptySceneNode(
            nodesRespondingToMouse,
            ID_INTERAKTIV + ID_FLAG_MAUSPFEILREAKTIV + ID_FLAG_KOLLIDIERBAR
    );
    interactiveNodes->setName( "interactiveNodes" );
    obstacleNodes = smgr_->addEmptySceneNode(
            worldNode,
            ID_HINDERNIS + ID_FLAG_KOLLIDIERBAR
    );
    obstacleNodes->setName( "obstacleNodes" );
    decorativeNodes = smgr_->addEmptySceneNode(
            worldNode,
            ID_WELTDEKORATION
    );
    decorativeNodes->setName( "decorativeNodes" );
    weatherNodes = smgr_->addEmptySceneNode(
            decorativeNodes,
            ID_WETTER
    );
    weatherNodes->setName( "weatherNodes" );
    bulletNodes = smgr_->addEmptySceneNode(
            worldNode,
            ID_GESCHOSSE
    );
    bulletNodes->setName( "bulletNodes" );
    staticObjects_.clear();
    npcs_.clear();
    updateTimer_ = TimerManager::getInstance().createTimer( 0.899f );
}



ObjectManager::~ObjectManager()
{
    // Niemals droppen, wenn Objekt nicht durch "create" erzeugt wurde!
    clearArrays();
    TimerManager::getInstance().removeTimer( updateTimer_ );
}



void ObjectManager::clearArrays()
{
    if ( staticObjects_.size() > 0 )
    {
        for ( register u32 i = 0; i < staticObjects_.size(); ++i )
        {
            if ( staticObjects_[ i ] )
            {
                Collision::getInstance().removeObjectFromRangedDetection(
                        staticObjects_[ i ] );
                delete staticObjects_[ i ];
                staticObjects_[ i ] = 0;
            }
        }
    }
    staticObjects_.clear();
    if ( npcs_.size() > 0 )
    {
        for ( register u32 i = 0; i < npcs_.size(); ++i )
        {
            if ( npcs_[ i ] )
            {
                Collision::getInstance().removeObjectFromRangedDetection(
                        npcs_[ i ] );
                delete npcs_[ i ];
                npcs_[ i ] = 0;
            }
        }
    }
    npcs_.clear();
}
