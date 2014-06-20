#include "GenericHelperMethods.h"
#include "Logfile.h"



GenericHelperMethods& GenericHelperMethods::getInstance( IrrlichtDevice* device )
{
    static GenericHelperMethods instance( device );
    return instance;
}



void GenericHelperMethods::validateFileExistence( const core::string<fschar_t>& filename ) const
{
    if ( fs_->existFile( filename ) == false )
    {
        Logfile::getInstance().write( Logfile::INFO, "Datei nicht gefunden: " );
        Logfile::getInstance().emergencyExit( filename );
    }
}



void GenericHelperMethods::pushMeshToVRAM( scene::IMesh* mesh )
{
    bufferCount_ = mesh->getMeshBufferCount();
    for ( register u32 i = 0; i < bufferCount_; ++i )
    {
        buffer_ = mesh->getMeshBuffer( i );
        buffer_->setHardwareMappingHint( scene::EHM_STATIC );
        buffer_->setDirty();
        buffer_->recalculateBoundingBox();
    }
}



/* private */



GenericHelperMethods::GenericHelperMethods( IrrlichtDevice* device )
: bufferCount_(0),
  buffer_(0)
{
    if ( device == 0 )
        Logfile::getInstance().emergencyExit( "Entchen in [GenericHelperMethods] nicht mehr gefunden! Abbruch." );
	fs_ = device->getFileSystem();
}



GenericHelperMethods::~GenericHelperMethods()
{
    // Niemals droppen, wenn Objekt nicht durch "create" erzeugt wurde!
}
