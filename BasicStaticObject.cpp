#include "BasicStaticObject.h"
#include "Collision.h"
#include "Constants.h"
#include "GenericHelperMethods.h"
#include "ObjectManager.h"
#include "Logfile.h"



BasicStaticObject::BasicStaticObject(
        const irr::core::stringc& objectData, irr::scene::ISceneManager* smgr, bool isParent )
: Basic3DObject( objectData, smgr, true ),
  node_(0),
  maxBBExtent_(VEC_3DF_NULL)
{
    if ( smgr_ == 0 )
        Logfile::getInstance().emergencyExit( "SceneManager in [BasicStaticObject] nicht mehr gefunden! Abbruch." );
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



irr::f32 BasicStaticObject::getCollisionRadius() const
{
    return 0.0f;
}



irr::scene::ISceneNode* BasicStaticObject::nodeInterface() const
{
    return static_cast<irr::scene::ISceneNode*>(node_);
}



const irr::core::vector3df& BasicStaticObject::getNextStep() const
{
    return VEC_3DF_NULL;
}



const irr::core::vector3df& BasicStaticObject::getMaxBoundingBoxExtent() const
{
    return maxBBExtent_;
}



//const ObjectConfiguration& BasicStaticObject::getObjectData() const
//{
//    objectData_2->mesh->materialCount = node_->getMaterialCount();
//    // objectData_2->mesh->offset ... DON'T TOUCH THIS!
//    objectData_2->mesh->position = node_->getAbsolutePosition();
//    objectData_2->mesh->rotation = node_->getRotation();
//    objectData_2->mesh->scale = node_->getScale();
//    for ( register u32 cnt = 0; cnt < objectData_2->mesh->materialCount; ++cnt )
//    {
//        objectData_2->materials->isBackFaceCulled[ cnt ] = node_->getMaterial( cnt ).BackfaceCulling;
//        objectData_2->materials->isLighted[ cnt ] = node_->getMaterial( cnt ).Lighting;
//        objectData_2->materials->isTransparent[ cnt ] = node_->getMaterial( cnt ).isTransparent();
//    }
//    // objectData_2->files ... DON'T TOUCH THIS!
//    return Basic3DObject::getObjectData();
//}



/* protected */



irr::scene::IMesh* BasicStaticObject::loadMesh()
{
    irr::scene::IMesh* mesh = 0;
    if ( extractor_->tryToExtractValue( "MFILE" ) )
    {
        irr::core::stringc meshFileName = extractor_->getExtractedValue();
        if ( meshFileName.size() == 0 )
        {
            createLogEntry( "Leerer Mesh-Dateiname" );
        }
        else
        {
            GenericHelperMethods::getInstance().validateFileExistence( meshFileName );
            irr::scene::IMesh* dummyMesh = smgr_->getMesh( meshFileName );
            mesh = smgr_->getMeshManipulator()->createMeshCopy( dummyMesh ); // TODO test if you can remove this part!
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
    irr::scene::IMeshManipulator* meshManipulator = smgr_->getMeshManipulator();
    irr::core::matrix4 matrix = irr::core::matrix4();

    smgr_->getVideoDriver()->setTransform( irr::video::ETS_WORLD, matrix );
    irr::scene::IMesh* dummyMesh = loadMesh();
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
        dummyMesh->drop(); // mesh is still grabbed by node_
        node_->setName( name_ );
        node_->setRotation( loadRotation() );
        node_->setPosition( loadPosition() );
        node_->updateAbsolutePosition();
        node_->setMaterialTexture( 0, loadMainTexture() );
        for ( irr::u32 i = 0; i < node_->getMaterialCount(); ++i )
            loadFilterAndEffects( node_->getMaterial( i ) );
        Collision::getInstance().addStaticMeshNodeToWorld( node_ );
        node_->setVisible( false );
        maxBBExtent_ = node_->getTransformedBoundingBox().getExtent();
    }
}
