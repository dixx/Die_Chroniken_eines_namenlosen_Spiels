#include "MapTile.h"
#include "Collision.h"
#include "Constants.h"
#include "GenericHelperMethods.h"
#include "ObjectManager.h"



MapTile::MapTile(
        const irr::core::stringc& objectData,
        irr::scene::ISceneManager* smgr,
        const irr::core::dimension2df& sectorDimension
)
: BasicStaticObject( objectData, smgr, true ),
  tileX_(-1),
  tileZ_(-1),
  sectorDimension_(sectorDimension)
{
    init();
    deleteExtractor();
}



MapTile::~MapTile()
{
    Collision::getInstance().removeObjectFromRangedDetection( this );
}



irr::s32 MapTile::getX() const
{
    return tileX_;
}



irr::s32 MapTile::getZ() const
{
    return tileZ_;
}



/* private */



void MapTile::init()
{
    irr::scene::IMeshManipulator* meshManipulator = smgr_->getMeshManipulator();
    irr::core::matrix4 matrix = irr::core::matrix4();

    smgr_->getVideoDriver()->setTransform( irr::video::ETS_WORLD, matrix );
    Collision::getInstance().removeNodeFromWorld( node_ );
    irr::scene::IMesh* dummyMesh = node_->getMesh();
    if ( dummyMesh )
    {
        irr::core::vector3df tileScale = irr::core::vector3df( 200.001f, 100.0f, 200.001f );
        if ( extractor_->tryToExtractValue( "MSCAL", "x", 0 ) )
            tileScale.X = irr::core::fast_atof( extractor_->getExtractedValue().c_str() );
        if ( extractor_->tryToExtractValue( "MSCAL", "x", 1 ) )
            tileScale.Y = irr::core::fast_atof( extractor_->getExtractedValue().c_str() );
        if ( extractor_->tryToExtractValue( "MSCAL", "x", 2 ) )
            tileScale.Z = irr::core::fast_atof( extractor_->getExtractedValue().c_str() );
        matrix.setScale( tileScale );
        // Position im Grid (Koordinaten sind in Ground:: schon validiert
        // worden)
        if ( extractor_->tryToExtractValue( "POSXZ", "x", 0 ) )
            tileX_ = irr::core::strtol10( extractor_->getExtractedValue().c_str() );
        if ( extractor_->tryToExtractValue( "POSXZ", "x", 1 ) )
            tileZ_ = irr::core::strtol10( extractor_->getExtractedValue().c_str() );
        matrix.setTranslation(
                irr::core::vector3df(
                        ( static_cast<irr::f32>( tileX_ ) + 0.5f ) * sectorDimension_.Width - static_cast<irr::f32>( tileX_ ),
                        0.0f,
                        ( static_cast<irr::f32>( tileZ_ ) + 0.5f ) * sectorDimension_.Height - static_cast<irr::f32>( tileZ_ )
                )
        );
        meshManipulator->transform( dummyMesh, matrix );
        meshManipulator->recalculateNormals( dummyMesh, true );
        GenericHelperMethods::getInstance().pushMeshToVRAM( dummyMesh );
        node_->updateAbsolutePosition();
        node_->setMaterialFlag( irr::video::EMF_LIGHTING, false );
        Collision::getInstance().addStaticMeshNodeToWorld( node_ );
        node_->setVisible( false );
    }
}
