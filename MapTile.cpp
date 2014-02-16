#include "MapTile.h"
#include "Collision.h"
#include "Constants.h"
#include "GenericHelperMethods.h"
#include "ObjectManager.h"



MapTile::MapTile(
        const core::stringc& objectData,
        scene::ISceneManager* smgr,
        const core::dimension2df& sectorDimension
)
: BasicStaticObject(objectData, smgr, true),
  tileX_(-1),
  tileZ_(-1),
  sectorDimension_(sectorDimension)
{
    init();
    deleteExtractor();
}



MapTile::~MapTile()
{
    // nothing to do here
    Collision::getInstance().removeObjectFromRangedDetection( this );
}



s32 MapTile::getX() const
{
    return tileX_;
}



s32 MapTile::getZ() const
{
    return tileZ_;
}



/* private */



void MapTile::init()
{
    scene::IMeshManipulator* meshManipulator = smgr_->getMeshManipulator();
    core::matrix4 matrix = core::matrix4();

    smgr_->getVideoDriver()->setTransform( video::ETS_WORLD, matrix );
    Collision::getInstance().removeNodeFromWorld( node_ );
    scene::IMesh* dummyMesh = node_->getMesh();
    if ( dummyMesh )
    {
        core::vector3df tileScale = core::vector3df( 200.001f, 100.0f, 200.001f );
        if ( extractor_->tryToExtractValue( "MSCAL", "x", 0 ) )
            tileScale.X = core::fast_atof(
                    extractor_->getExtractedValue().c_str() );
        if ( extractor_->tryToExtractValue( "MSCAL", "x", 1 ) )
            tileScale.Y = core::fast_atof(
                    extractor_->getExtractedValue().c_str() );
        if ( extractor_->tryToExtractValue( "MSCAL", "x", 2 ) )
            tileScale.Z = core::fast_atof(
                    extractor_->getExtractedValue().c_str() );
        matrix.setScale( tileScale );
        // Position im Grid (Koordinaten sind in Ground:: schon validiert
        // worden)
        if ( extractor_->tryToExtractValue( "POSXZ", "x", 0 ) )
            tileX_ = core::strtol10( extractor_->getExtractedValue().c_str() );
        if ( extractor_->tryToExtractValue( "POSXZ", "x", 1 ) )
            tileZ_ = core::strtol10( extractor_->getExtractedValue().c_str() );
        matrix.setTranslation(
                core::vector3df(
                        static_cast<f32>( tileX_ ) * sectorDimension_.Width +
                                sectorDimension_.Width / 2,
                        0.0f,
                        static_cast<f32>( tileZ_ ) * sectorDimension_.Height +
                                sectorDimension_.Height / 2
                )
        );
        meshManipulator->transform( dummyMesh, matrix );
        meshManipulator->recalculateNormals( dummyMesh, true );
        GenericHelperMethods::getInstance().pushMeshToVRAM( dummyMesh );
        node_->updateAbsolutePosition();
        node_->setMaterialFlag( video::EMF_LIGHTING, false );
        Collision::getInstance().addStaticMeshNodeToWorld( node_ );
        node_->setVisible( false );
    }
}
