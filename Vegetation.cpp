#include "Vegetation.h"
#include "Ground.h"
#include "GenericHelperMethods.h"
#include "Logfile.h"
#include "ObjectManager.h"



Vegetation::Vegetation( scene::ISceneManager* smgr )
: smgr_(smgr)
{
    if ( smgr_ == 0 )
    {
        Logfile::getInstance().emergencyExit(
                "SceneManager in [Vegetation] nicht mehr gefunden! Abbruch."
        );
    }
    meshManipulator_ = smgr_->getMeshManipulator();
    grassMesh_ = new scene::SMesh(); // same as "create", ReferenceCounter = 1
    grassNode_ = new BufferCullMeshSceneNode(
            grassMesh_,
            ObjectManager::getInstance().getBaseNodeByType( "gras" ),
            smgr_,
            ObjectManager::getInstance().getBaseIdByType( "gras" )
    );
    grassNode_->setVisible( true );
    grassNode_->setMaterialFlag(video::EMF_WIREFRAME, true);
}



Vegetation::~Vegetation()
{
    // Niemals droppen, wenn Objekt nicht durch "create" erzeugt wurde!
    if ( grassNode_ )
    {
        grassNode_->getMesh()->drop();
        grassNode_->remove();  // drop und delete werden implizit ausgeführt
        grassNode_ = 0;
    }
    while ( grassMesh_->getReferenceCount() > 0 )
        grassMesh_->drop();
}



void Vegetation::create()
{
    core::matrix4 matrix = core::matrix4();
    scene::SMesh* dummy = 0;
    core::vector3df position;
    GenericHelperMethods& helper = GenericHelperMethods::getInstance();
    Ground& ground = Ground::getInstance();

    scene::SMeshBuffer* buffer = new scene::SMeshBuffer();
    grassMesh_->addMeshBuffer( buffer );
    buffer->drop(); // is already grabbed by grassMesh_ :)


    smgr_->getVideoDriver()->setTransform( video::ETS_WORLD, matrix );
    helper.validateFileExistence( "GFX/OBJECTS/3ds__flow2.3ds" );
    scene::IMesh* grass = smgr_->getMesh( "GFX/OBJECTS/3ds__flow2.3ds" );
    if ( !grass ) return;
    meshManipulator_->scale( grass, core::vector3df( 0.01f, 0.01f, 0.01f ) );
    matrix.setTranslation( core::vector3df() ); // TODO calculate correct 0-position here!
    meshManipulator_->transform( dummy, matrix );
    helper.pushMeshToVRAM( grass );
    Logfile::getInstance().dbg( "scale: ", grass->getBoundingBox().getExtent() );
    Logfile::getInstance().dbg( "min_edge: ", grass->getBoundingBox().MinEdge );
    Logfile::getInstance().dbg( "max_edge: ", grass->getBoundingBox().MaxEdge );

    // create a lot of grass patches
    position = core::vector3df( 10.0f, 0.0f, 10.0f ); // randomize intelligent!
    position = ground.getHeightFromPosition( position );
    matrix = core::matrix4();
    dummy = meshManipulator_->createMeshCopy( grass );
    Logfile::getInstance().dbg( "copied_buffer_count: ", dummy->getMeshBuffer(0)->getVertexCount() );
    matrix.setTranslation( position );
    meshManipulator_->transform( dummy, matrix );
    Logfile::getInstance().dbg( "copied_min_edge: ", dummy->getBoundingBox().MinEdge );
    // add grass patch to the overall grass mesh, to the right buffer
//    // Best Fit
//    bool addbuffer = true;
//    scene::SMeshBuffer *hbuf;
//    for ( u32 b_id = 0; b_id < grasmesh->getMeshBufferCount(); ++b_id )
//    {
//        // search all available buffers
//        hbuf = (scene::SMeshBuffer*)grasmesh->getMeshBuffer( b_id );
//        if ( hbuf->Material != buffer->Material )
//            continue;  // material different
//        if ( hbuf->getBoundingBox().getCenter().getDistanceFrom(
//                buffer->getBoundingBox().getCenter() ) > 2000.f )
//            continue;  // too far away for grouping
//        if ( hbuf->getVertexCount() >= (
//                //65535 - buffer->getVertexCount() ) )
//                32765 - buffer->getVertexCount() ) )
//            continue;  // too many vertices
//        if ( hbuf->getVertexType() != buffer->getVertexType() )
//            continue;  // different vertex type
//        // this buffer fits our needs, add new buffer to this one
//        hbuf->append(
//                buffer->getVertices(),
//                buffer->getVertexCount(),
//                buffer->getIndices(),
//                buffer->getIndexCount()
//        );
//        //statistik
//        if ( hbuf->getVertexCount() > max_vert )
//            max_vert = hbuf->getVertexCount();
//        addbuffer = false;
//        break;
//    }
//    // if no fitting buffer is found, create new one
//    if ( addbuffer ) grasmesh->addMeshBuffer( buffer );
    grassMesh_->getMeshBuffer(0)->append(
            dummy->getMeshBuffer(0)->getVertices(),
            dummy->getMeshBuffer(0)->getVertexCount(),
            dummy->getMeshBuffer(0)->getIndices(),
            dummy->getMeshBuffer(0)->getIndexCount()
    );
    dummy->drop();
    smgr_->getMeshCache()->removeMesh( dummy );


    meshManipulator_->recalculateNormals( grassMesh_, true ); // think it over,
    // should we recalculate all normals to point upwards?
    helper.pushMeshToVRAM( grassMesh_ );

    helper.validateFileExistence( "GFX/flow2.png" );
    video::ITexture* gras1 =
            smgr_->getVideoDriver()->getTexture( "GFX/flow2.png" );
    grassMesh_->getMeshBuffer(0)->getMaterial().setTexture( 0, gras1 );
    Logfile::getInstance().dbg( "node_pos: ", grassNode_->getAbsolutePosition() );
    Logfile::getInstance().dbg( "node_min_edge: ", grassNode_->getTransformedBoundingBox().MinEdge );
    Logfile::getInstance().dbg( "node_max_edge: ", grassNode_->getTransformedBoundingBox().MaxEdge );
    Logfile::getInstance().dbg( "node_mesh_min_edge: ", grassNode_->getMesh()->getMeshBuffer(0)->getBoundingBox().MinEdge );
    Logfile::getInstance().dbg( "node_mesh_max_edge: ", grassNode_->getMesh()->getMeshBuffer(0)->getBoundingBox().MaxEdge );

    // cleanup
    smgr_->getMeshCache()->removeMesh( grass );
}



void Vegetation::update()
{
    //grassNode_->setVisible( true );
    //grassNode_->setMaterialFlag(video::EMF_WIREFRAME, true);
    //grassNode_->setDebugDataVisible( scene::EDS_FULL );
}



/* private */
