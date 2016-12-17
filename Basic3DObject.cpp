#include "Basic3DObject.h"
#include "Constants.h"
#include "GenericHelperMethods.h"
#include "Logfile.h"



Basic3DObject::Basic3DObject( const irr::core::stringc& objectData, irr::scene::ISceneManager* smgr, bool isParent )
: type_("<unknown>"),
  name_("<noname>"),
  objectData_(objectData),
  objectData_2(0),
  extractor_(0),
  smgr_(smgr)
{
    if ( smgr_ == 0 )
        Logfile::getInstance().emergencyExit( "SceneManager in [Basic3DObject] nicht mehr gefunden! Abbruch." );
    if ( objectData_.size() != 0 )
    {
        extractor_ = new ObjectParamsExtractor( objectData_ );
        if ( extractor_->tryToExtractValue( "ONAME" ) )
            name_ = extractor_->getExtractedValue();
        if ( extractor_->tryToExtractValue( "OTYPE" ) )
            type_ = extractor_->getExtractedValue();
        if ( name_.size() == 0 || name_ == "<noname>" )
            createLogEntry( "Kein Name für Objekt" );
        if ( type_.size() == 0 || type_ == "<unknown>" )
            createLogEntry( "Kein Typ für Objekt" );
        if ( !isParent )
            deleteExtractor();
    }
}



Basic3DObject::~Basic3DObject()
{
    if ( extractor_ )
        deleteExtractor();
}



const irr::core::stringc& Basic3DObject::getName() const
{
    return name_;
}



const irr::core::stringc& Basic3DObject::getType() const
{
    return type_;
}



//const ObjectConfiguration& Basic3DObject::getObjectData() const
//{
//    objectData_2->object->type = ObjectConfigurationContextForObject::DEKORATION;
//    objectData_2->node->name = name_;
//    return *objectData_2;
//}



/* protected */



void Basic3DObject::createLogEntry( const irr::core::stringc& message )
{
    Logfile& logfile = Logfile::getInstance();
    logfile.write( Logfile::INFO, message );
    logfile.writeLine( Logfile::INFO, " in Objektbeschreibung!" );
    logfile.writeLine( Logfile::INFO, objectData_ );
}



void Basic3DObject::deleteExtractor()
{
    delete extractor_;
    extractor_ = 0;
}



irr::core::vector3df Basic3DObject::loadScale()
{
    irr::core::vector3df scale = irr::core::vector3df( 1.0f );
    if ( extractor_->tryToExtractValue( "MSCAL", "x", 0 ) )
        scale.X = irr::core::fast_atof( extractor_->getExtractedValue().c_str() );
    if ( extractor_->tryToExtractValue( "MSCAL", "x", 1 ) )
        scale.Y = irr::core::fast_atof( extractor_->getExtractedValue().c_str() );
    if ( extractor_->tryToExtractValue( "MSCAL", "x", 2 ) )
        scale.Z = irr::core::fast_atof( extractor_->getExtractedValue().c_str() );
    return scale;
}



irr::core::vector3df Basic3DObject::loadOffset()
{
    irr::core::vector3df offset = VEC_3DF_NULL;
    if ( extractor_->tryToExtractValue( "MOFFS", "x", 0 ) )
        offset.X = irr::core::fast_atof( extractor_->getExtractedValue().c_str() );
    if ( extractor_->tryToExtractValue( "MOFFS", "x", 1 ) )
        offset.Y = irr::core::fast_atof( extractor_->getExtractedValue().c_str() );
    if ( extractor_->tryToExtractValue( "MOFFS", "x", 2 ) )
        offset.Z = irr::core::fast_atof( extractor_->getExtractedValue().c_str() );
    return offset;
}



irr::core::vector3df Basic3DObject::loadRotation()
{
    irr::core::vector3df rotation = VEC_3DF_NULL;
    if ( extractor_->tryToExtractValue( "MROTA", "x", 0 ) )
        rotation.X = irr::core::fast_atof( extractor_->getExtractedValue().c_str() );
    if ( extractor_->tryToExtractValue( "MROTA", "x", 1 ) )
        rotation.Y = irr::core::fast_atof( extractor_->getExtractedValue().c_str() );
    if ( extractor_->tryToExtractValue( "MROTA", "x", 2 ) )
        rotation.Z = irr::core::fast_atof( extractor_->getExtractedValue().c_str() );
    return rotation;
}



irr::core::vector3df Basic3DObject::loadPosition()
{
    irr::core::vector3df position = VEC_3DF_NULL;
    if ( extractor_->tryToExtractValue( "POSXZ", "x", 0 ) )
        position.X = irr::core::fast_atof( extractor_->getExtractedValue().c_str() );
    if ( extractor_->tryToExtractValue( "POSXZ", "x", 1 ) )
        position.Z = irr::core::fast_atof( extractor_->getExtractedValue().c_str() );
    return position;
}



irr::video::ITexture* Basic3DObject::loadMainTexture()
{
    if ( extractor_->tryToExtractValue( "MTEX0" ) == false )
    {
        createLogEntry( "Kein Textur-Dateiname für Material 0" );
        return 0;
    }
    irr::core::stringc textureFileName = extractor_->getExtractedValue();
    if ( textureFileName.size() == 0 )
    {
        createLogEntry( "Leerer Textur-Dateiname für Material 0" );
        return 0;
    }
    GenericHelperMethods::getInstance().validateFileExistence( textureFileName );
    irr::video::ITexture* texture = smgr_->getVideoDriver()->getTexture( textureFileName );
    if ( extractor_->tryToExtractValue( "MTRAN" ) )
    {
        if ( extractor_->getExtractedValue().find( "ja" ) != -1 )
        {
            smgr_->getVideoDriver()->setTextureCreationFlag( irr::video::ETCF_CREATE_MIP_MAPS, false );
            smgr_->getVideoDriver()->disableFeature( irr::video::EVDF_BILINEAR_FILTER, true );
            smgr_->getVideoDriver()->makeColorKeyTexture( texture, VEC_2DI_NULL );
            smgr_->getVideoDriver()->disableFeature( irr::video::EVDF_BILINEAR_FILTER, false );
            smgr_->getVideoDriver()->setTextureCreationFlag( irr::video::ETCF_CREATE_MIP_MAPS, true );
        }
    }
    return texture;
}



void Basic3DObject::loadFilterAndEffects( irr::video::SMaterial& material )
{
    material.MaterialType = irr::video::EMT_SOLID;
    material.setFlag( irr::video::EMF_BACK_FACE_CULLING, true );
    if ( extractor_->tryToExtractValue( "MTRAN" ) )
    {
        if ( extractor_->getExtractedValue().find( "ja" ) != -1 )
        {
            material.MaterialType = irr::video::EMT_TRANSPARENT_ALPHA_CHANNEL;
        }
    }
    material.setFlag( irr::video::EMF_LIGHTING, true );
    material.setFlag( irr::video::EMF_ANISOTROPIC_FILTER, true );
    material.setFlag( irr::video::EMF_ANTI_ALIASING, true );
    material.setFlag( irr::video::EMF_BILINEAR_FILTER, true );
    material.setFlag( irr::video::EMF_FOG_ENABLE, true );
    material.setFlag( irr::video::EMF_GOURAUD_SHADING, true );
    material.setFlag( irr::video::EMF_ZBUFFER, true );
}



/* private */
