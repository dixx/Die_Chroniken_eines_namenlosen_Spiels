#include "BasicLifeform.h"
#include "Collision.h"
#include "Constants.h"
#include "GenericHelperMethods.h"
#include "Constants.h"
#include "Logfile.h"
#include "ObjectManager.h"



BasicLifeform::BasicLifeform(
        const core::stringc& objectData,
        scene::ISceneManager* smgr,
        bool isParent
)
: Basic3DObject(objectData, smgr, true),
  node_(0),
  isMoving_(false),
  wasMoving_(false),
  speed_(1.0f),
  movementDelta_(0.0f),
  nextStep_(VEC_3DF_NULL)
{
    if ( smgr_ == 0 )
    {
        Logfile::getInstance().emergencyExit(
                "SceneManager in [BasicLifeform] nicht mehr gefunden! Abbruch."
        );
    }
    init();
    if ( !isParent )
        deleteExtractor();
}



BasicLifeform::~BasicLifeform()
{
    // Niemals droppen, wenn Objekt nicht durch "create" erzeugt wurde!
    Collision::getInstance().removeNodeFromWorld( node_ );
    node_->removeAll(); // removes children
    node_->remove();
}



void BasicLifeform::update( f32 frameDeltaTime )
{
    movementDelta_ = speed_ * frameDeltaTime;
    calculateNextStep();
}



scene::IAnimatedMeshSceneNode* BasicLifeform::getNode() const
{
    return node_;
}



f32 BasicLifeform::getCollisionRadius() const
{
    return collisionRadius_;
}



scene::ISceneNode* BasicLifeform::nodeInterface() const
{
    return static_cast<scene::ISceneNode*>(node_);
}



const core::vector3df& BasicLifeform::getNextStep() const
{
    return nextStep_;
}



/* protected */



scene::IAnimatedMesh* BasicLifeform::loadMesh()
{
    scene::IAnimatedMesh* mesh = 0;
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
            mesh = smgr_->getMesh( meshFileName );
        }
    }
    else
    {
        createLogEntry( "Kein Mesh-Dateiname" );
    }
    return mesh;
}



/* private */



void BasicLifeform::init()
{
    core::matrix4 matrix = core::matrix4();

    smgr_->getVideoDriver()->setTransform( video::ETS_WORLD, matrix );
    node_ = smgr_->addAnimatedMeshSceneNode(
            loadMesh(),
            ObjectManager::getInstance().getBaseNodeByType( type_ ),
            ObjectManager::getInstance().getBaseIdByType( type_ )
    );
    node_->setScale( loadScale() );
    node_->setName( name_ );
    node_->setRotation( loadRotation() );
    node_->setPosition( loadPosition() + loadOffset() );
    node_->updateAbsolutePosition();
    node_->setMaterialTexture( 0, loadMainTexture() );
    for ( u32 i = 0; i < node_->getMaterialCount(); ++i )
        loadFilterAndEffects( node_->getMaterial( i ) );
    Collision::getInstance().addAnimatedMeshNodeToWorld( node_ );
    node_->setVisible( false );
    calculateCollisionRadius();
}



void BasicLifeform::calculateNextStep()
{
    nextStep_ = VEC_3DF_NULL;//targetPosition_ - currentPosition_;
    nextStep_.setLength( movementDelta_ );
}



void BasicLifeform::calculateCollisionRadius()
{
    core::vector3df dummy = node_->getTransformedBoundingBox().getExtent();
    dummy.Y = 0.0f;
    collisionRadius_ = dummy.getLength() * 0.3f;
}
