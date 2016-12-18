#include "Vegetation.h"
#include "Ground.h"
#include "GenericHelperMethods.h"
#include "Logfile.h"
#include "ObjectManager.h"
#include "Zufall.h"



Vegetation::Vegetation( irr::scene::ISceneManager* smgr )
: smgr_(smgr),
  grassNode_(0)
{
    if ( smgr_ == 0 )
        Logfile::getInstance().emergencyExit( "SceneManager in [Vegetation] nicht mehr gefunden! Abbruch." );
    meshManipulator_ = smgr_->getMeshManipulator();
    grassMesh_ = new irr::scene::SMesh(); // same as "create", ReferenceCounter = 1
    irr::scene::SMeshBuffer* buffer = new irr::scene::SMeshBuffer();
    grassMesh_->addMeshBuffer( buffer );
    buffer->drop(); // is already grabbed by grassMesh_ :)
}



// BUG irgendwo hier!
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
    irr::core::matrix4 matrix = irr::core::matrix4();
    irr::core::vector3df position;
    GenericHelperMethods& helper = GenericHelperMethods::getInstance();
    Ground& ground = Ground::getInstance();
    Zufall& zufall = Zufall::getInstance();

    // create the master grass patch
    smgr_->getVideoDriver()->setTransform( irr::video::ETS_WORLD, matrix );
    helper.validateFileExistence( "GFX/OBJECTS/3ds__grass.3ds" );
    irr::scene::IMesh* grass = smgr_->getMesh( "GFX/OBJECTS/3ds__grass.3ds" );
    if ( !grass )
    {
        Logfile::getInstance().writeLine( Logfile::INFO, "Gras konnte nicht geladen werden!" );
        return;
    }
    meshManipulator_->scale( grass, irr::core::vector3df( 0.006f ) ); // TODO calculate correct size!
    //matrix.setTranslation( core::vector3df() ); // TODO calculate correct 0-position here!
    //meshManipulator_->transform( grass, matrix );
    helper.pushMeshToVRAM( grass );

    helper.validateFileExistence( "GFX/grass.tga" );
    irr::video::ITexture* gras1 = smgr_->getVideoDriver()->getTexture( "GFX/grass.tga" );
    smgr_->getVideoDriver()->makeColorKeyTexture( gras1, VEC_2DI_NULL );

    // create a lot of grass patches
    irr::scene::SMesh* patch = 0;
    irr::f32 x, z;
    bool addbuffer = true;
    irr::scene::SMeshBuffer* patchBuffer;
    irr::scene::SMeshBuffer* grasMeshBuffer;
    for( register irr::u32 i = 0; i < 4000; ++i )
    {
        x = zufall.getFloatBetween( 0.0f, 50.0f );
        z = zufall.getFloatBetween( 0.0f, 50.0f );
        position = irr::core::vector3df( x, ground.getHeight( x, z ), z ); // randomize intelligent!
        patch = meshManipulator_->createMeshCopy( grass );
        meshManipulator_->scale( patch, irr::core::vector3df( zufall.getFloatBetween( 1.0f, 3.0f ) ) );
        matrix = irr::core::matrix4();
        matrix.setRotationDegrees( irr::core::vector3df( 0.0f, zufall.getFloatBetween( 0.0f, 360.0f ), 0.0f ) );
        meshManipulator_->transform( patch, matrix );
        matrix.setTranslation( position );
        meshManipulator_->transform( patch, matrix );
        // add grass patch to the overall grass mesh, to the right buffer, 'Best Fit'
        addbuffer = true;
        // search all available grasMeshBuffers
        for ( register irr::u32 bufferIndex = 0; bufferIndex < grassMesh_->getMeshBufferCount(); ++bufferIndex )
        {
            grasMeshBuffer = (irr::scene::SMeshBuffer*)grassMesh_->getMeshBuffer( bufferIndex );
            patchBuffer = (irr::scene::SMeshBuffer*)patch->getMeshBuffer(0);
            if ( grasMeshBuffer->Material != patchBuffer->Material )
                continue;  // material different
            if ( grasMeshBuffer->BoundingBox.getCenter().getDistanceFrom( patchBuffer->BoundingBox.getCenter() )
                    > 400.0f )
                continue;  // too far away for grouping
            if ( grasMeshBuffer->getVertexCount() >= ( 32765 - patchBuffer->getVertexCount() ) )
                continue;  // too many vertices
            if ( grasMeshBuffer->getVertexType() != patchBuffer->getVertexType() )
                continue;  // different vertex type
            // this buffer fits our needs, add new buffer to this one
            grasMeshBuffer->append(
                    patchBuffer->getVertices(),
                    patchBuffer->getVertexCount(),
                    patchBuffer->getIndices(),
                    patchBuffer->getIndexCount()
            );
            addbuffer = false;
            break;
        }
        // if no fitting buffer is found, create new one
        if ( addbuffer )
            grassMesh_->addMeshBuffer( patchBuffer );
        patch->drop();
    }

    meshManipulator_->recalculateNormals( grassMesh_, true ); // should we recalculate all normals to point upwards?
    helper.pushMeshToVRAM( grassMesh_ );
    grassMesh_->recalculateBoundingBox();

    for ( irr::u32 bufferIndex = 0; bufferIndex < grassMesh_->getMeshBufferCount(); ++bufferIndex )
        grassMesh_->getMeshBuffer(bufferIndex)->getMaterial().setTexture( 0, gras1 );

    grassNode_ = new BufferCullMeshSceneNode(
            grassMesh_,
            ObjectManager::getInstance().getBaseNodeByType( "gras" ),
            smgr_,
            ObjectManager::getInstance().getBaseIdByType( "gras" )
    );
    grassMesh_->drop();
    grassNode_->setMaterialType( irr::video::EMT_TRANSPARENT_ALPHA_CHANNEL );
    grassNode_->setMaterialFlag( irr::video::EMF_BACK_FACE_CULLING, false );
    grassNode_->setMaterialFlag( irr::video::EMF_LIGHTING, true );
    grassNode_->setMaterialFlag( irr::video::EMF_FOG_ENABLE, true );
    // einige Filter und Shader, verbessern Textur wenn TRUE
    grassNode_->setMaterialFlag( irr::video::EMF_BILINEAR_FILTER, true );
    //grassNode_->setMaterialFlag( video::EMF_ANISOTROPIC_FILTER, true );
    grassNode_->setMaterialFlag( irr::video::EMF_ANTI_ALIASING, true );
    grassNode_->setMaterialFlag( irr::video::EMF_ZBUFFER, true );
    grassNode_->setMaterialFlag( irr::video::EMF_ZWRITE_ENABLE, true );
    grassNode_->setVisible( true );
    grassNode_->setDebugDataVisible( irr::scene::EDS_BBOX_BUFFERS );

    // cleanup
    smgr_->getMeshCache()->removeMesh( patch );
    smgr_->getMeshCache()->removeMesh( grass );
}



void Vegetation::update()
{
    //grassNode_->setVisible( true );
    //grassNode_->setMaterialFlag(video::EMF_WIREFRAME, true);
    //grassNode_->setDebugDataVisible( scene::EDS_FULL );
}



/* private */
