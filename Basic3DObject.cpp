#include "Basic3DObject.h"
#include "Constants.h"
#include "GenericHelperMethods.h"
#include "Logfile.h"



Basic3DObject::Basic3DObject(
        const core::stringc& objectData,
        scene::ISceneManager* smgr,
        bool isParent
)
: type_("<unknown>"),
  name_("<noname>"),
  objectData_(objectData),
  extractor_(0),
  smgr_(smgr)
{
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



const core::stringc& Basic3DObject::getName() const
{
    return name_;
}



const core::stringc& Basic3DObject::getType() const
{
    return type_;
}



core::stringc Basic3DObject::getObjectData()
{
    return "";
}



/* protected */



void Basic3DObject::createLogEntry( const core::stringc& message )
{
    Logfile::getInstance().write( Logfile::INFO, message );
    Logfile::getInstance().writeLine(
            Logfile::INFO, " in Objektbeschreibung!" );
    Logfile::getInstance().writeLine( Logfile::INFO, objectData_ );
}



void Basic3DObject::deleteExtractor()
{
    delete extractor_;
    extractor_ = 0;
}



core::vector3df Basic3DObject::loadScale()
{
    core::vector3df scale = core::vector3df( 1.0f );
    if ( extractor_->tryToExtractValue( "MSCAL", "x", 0 ) )
        scale.X = core::fast_atof(
                extractor_->getExtractedValue().c_str() );
    if ( extractor_->tryToExtractValue( "MSCAL", "x", 1 ) )
        scale.Y = core::fast_atof(
                extractor_->getExtractedValue().c_str() );
    if ( extractor_->tryToExtractValue( "MSCAL", "x", 2 ) )
        scale.Z = core::fast_atof(
                extractor_->getExtractedValue().c_str() );
    return scale;
}



core::vector3df Basic3DObject::loadOffset()
{
    core::vector3df offset = VEC_3DF_NULL;
    if ( extractor_->tryToExtractValue( "MOFFS", "x", 0 ) )
        offset.X = core::fast_atof(
                extractor_->getExtractedValue().c_str() );
    if ( extractor_->tryToExtractValue( "MOFFS", "x", 1 ) )
        offset.Y = core::fast_atof(
                extractor_->getExtractedValue().c_str() );
    if ( extractor_->tryToExtractValue( "MOFFS", "x", 2 ) )
        offset.Z = core::fast_atof(
                extractor_->getExtractedValue().c_str() );
    return offset;
}



core::vector3df Basic3DObject::loadRotation()
{
    core::vector3df rotation = VEC_3DF_NULL;
    if ( extractor_->tryToExtractValue( "MROTA", "x", 0 ) )
        rotation.X = core::fast_atof(
                extractor_->getExtractedValue().c_str() );
    if ( extractor_->tryToExtractValue( "MROTA", "x", 1 ) )
        rotation.Y = core::fast_atof(
                extractor_->getExtractedValue().c_str() );
    if ( extractor_->tryToExtractValue( "MROTA", "x", 2 ) )
        rotation.Z = core::fast_atof(
                extractor_->getExtractedValue().c_str() );
    return rotation;
}



core::vector3df Basic3DObject::loadPosition()
{
    core::vector3df position = VEC_3DF_NULL;
    if ( extractor_->tryToExtractValue( "POSXZ", "x", 0 ) )
        position.X = core::fast_atof(
                extractor_->getExtractedValue().c_str() );
    if ( extractor_->tryToExtractValue( "POSXZ", "x", 1 ) )
        position.Z = core::fast_atof(
                extractor_->getExtractedValue().c_str() );
    return position;
}



video::ITexture* Basic3DObject::loadMainTexture()
{
    if ( extractor_->tryToExtractValue( "MTEX0" ) == false )
    {
        createLogEntry( "Kein Textur-Dateiname für Material 0" );
        return 0;
    }
    core::stringc textureFileName = extractor_->getExtractedValue();
    if ( textureFileName.size() == 0 )
    {
        createLogEntry( "Leerer Textur-Dateiname für Material 0" );
        return 0;
    }
    GenericHelperMethods::getInstance().validateFileExistence(
            textureFileName );
    return smgr_->getVideoDriver()->getTexture( textureFileName );
}



void Basic3DObject::loadFilterAndEffects( video::SMaterial& material )
{
    material.MaterialType = video::EMT_SOLID;
    material.setFlag( video::EMF_LIGHTING, true );
    material.setFlag( video::EMF_BACK_FACE_CULLING, true );
    material.setFlag( video::EMF_ANISOTROPIC_FILTER, true );
    material.setFlag( video::EMF_ANTI_ALIASING, true );
    material.setFlag( video::EMF_BILINEAR_FILTER, true );
    material.setFlag( video::EMF_FOG_ENABLE, true );
    material.setFlag( video::EMF_GOURAUD_SHADING, true );
    material.setFlag( video::EMF_ZBUFFER, true );
}



/* private */
