#include "BasicStaticObject.h"
#include "Collision.h"
#include "Constants.h"
#include "GenericHelperMethods.h"
#include "ObjectManager.h"
#include "Logfile.h"



BasicStaticObject::BasicStaticObject(
        const core::stringc& objectData,
        scene::ISceneManager* smgr,
        bool isParent
)
: Basic3DObject(objectData, smgr, true),
  node_(0),
  nextStep_(VEC_3DF_NULL)
{
    init();
    if ( !isParent )
        deleteExtractor();
}



BasicStaticObject::~BasicStaticObject()
{
    if ( node_ )
    {
        Collision::getInstance().removeNodeFromWorld( node_ );
        node_->getMesh()->drop();
        node_->remove();  // drop und delete werden implizit ausgeführt
        node_ = 0;
    }
}



BufferCullMeshSceneNode* BasicStaticObject::getNode() const
{
    return node_;
}



f32 BasicStaticObject::getCollisionRadius() const
{
    return 0.0f;
}



scene::ISceneNode* BasicStaticObject::nodeInterface() const
{
    return static_cast<scene::ISceneNode*>(node_);
}



const core::vector3df& BasicStaticObject::getNextStep() const
{
    return nextStep_;
}



/* protected */



scene::IMesh* BasicStaticObject::loadMesh()
{
    scene::IMesh* mesh = 0;
    if ( extractor_->tryToExtractValue( "MFILE" ) )
    {
        core::stringc meshFileName = extractor_->getExtractedValue();
        if ( meshFileName.size() == 0 )
        {
            createLogEntry( "Leerer Mesh-Dateiname" );
        }
        else
        {
            GenericHelperMethods::getInstance().validateFileExistence(
                    meshFileName );
            scene::IMesh* dummyMesh = smgr_->getMesh( meshFileName );
            mesh = smgr_->getMeshManipulator()->createMeshCopy(
                    dummyMesh ); // TODO test if you can remove this part!
            smgr_->getMeshCache()->removeMesh( dummyMesh );
        }
    }
    else
    {
        createLogEntry( "Kein Mesh-Dateiname" );
    }
    return mesh;
}



/* private */



void BasicStaticObject::init()
{
    scene::IMeshManipulator* meshManipulator = smgr_->getMeshManipulator();
    core::matrix4 matrix = core::matrix4();

    smgr_->getVideoDriver()->setTransform( video::ETS_WORLD, matrix );
    scene::IMesh* dummyMesh = loadMesh();
    if ( dummyMesh )
    {
        matrix.setScale( loadScale() );
        matrix.setTranslation( loadOffset() );
        meshManipulator->transform( dummyMesh, matrix );
        meshManipulator->recalculateNormals( dummyMesh, true );
        GenericHelperMethods::getInstance().pushMeshToVRAM( dummyMesh );
        node_ = new BufferCullMeshSceneNode(
                dummyMesh,
                ObjectManager::getInstance().getBaseNodeByType( type_ ),
                smgr_,
                ObjectManager::getInstance().getBaseIdByType( type_ )
        );
        dummyMesh->drop();
        node_->setName( name_ );
        node_->setRotation( loadRotation() );
        node_->setPosition( loadPosition() );
        node_->updateAbsolutePosition();
        node_->setMaterialTexture( 0, loadMainTexture() );
        for ( u32 i = 0; i < node_->getMaterialCount(); ++i )
            loadFilterAndEffects( node_->getMaterial( i ) );
        Collision::getInstance().addStaticMeshNodeToWorld( node_ );
        node_->setVisible( false );
    }
}
