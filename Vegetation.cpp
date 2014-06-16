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
    grassMesh_->addMeshBuffer( new scene::SMeshBuffer() );
    grassNode_ = new BufferCullMeshSceneNode(
            grassMesh_,
            ObjectManager::getInstance().getBaseNodeByType( "gras" ),
            smgr_,
            ObjectManager::getInstance().getBaseIdByType( "gras" )
    );
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

    smgr_->getVideoDriver()->setTransform( video::ETS_WORLD, matrix );
    helper.validateFileExistence( "GFX/OBJECTS/3ds__flow2.3ds" );
    scene::IMesh* grass = smgr_->getMesh( "GFX/OBJECTS/3ds__flow2.3ds" );
    if ( !grass ) return;
    meshManipulator_->scale( grass, core::vector3df( 0.01f, 0.01f, 0.01f ) );

    // create a lot of grass patches
    position = core::vector3df( 10.0f, 0.0f, 10.0f ); // randomize intelligent!
    position = ground.getHeightFromPosition( position );
    matrix = core::matrix4();
    dummy = meshManipulator_->createMeshCopy( grass );
    // (you'll need to cast SMesh->getMeshBuffer to an SMeshBuffer)
    Logfile::getInstance().dbg( "c: ", dummy->getMeshBuffer(0)->getVertexCount() );
    matrix.setTranslation( position );
    meshManipulator_->transform( dummy, matrix );
    // add grass patch to the overall grass mesh, to the right buffer
    grassMesh_->getMeshBuffer(0)->append(
            dummy->getMeshBuffer(0)
    );
    dummy->drop();


    meshManipulator_->recalculateNormals( grassMesh_, true ); // think it over,
    // should we recalculate all normals to point upwards?
    helper.pushMeshToVRAM( grassMesh_ );

    helper.validateFileExistence( "GFX/flow2.png" );
    video::ITexture* gras1 =
            smgr_->getVideoDriver()->getTexture( "GFX/flow2.png" );
    grassMesh_->getMeshBuffer(0)->getMaterial().setTexture( 0, gras1 );
    grassNode_->setMesh( grassMesh_ );

    // cleanup
    smgr_->getMeshCache()->removeMesh( grass );
}



void Vegetation::update()
{
    ;
}



/* private */
