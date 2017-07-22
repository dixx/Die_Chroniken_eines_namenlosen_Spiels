#include "Testhelper.h"

Testhelper::Testhelper()
{
    irr::SIrrlichtCreationParameters params;
    params.DriverType = irr::video::EDT_NULL;
    params.LoggingLevel = irr::ELL_WARNING;
    graphicEngine_ = irr::createDeviceEx( params );
    fileSystem_ = graphicEngine_->getFileSystem();
}

Testhelper::~Testhelper()
{
    fileSystem_ = 0;
    if( graphicEngine_ )
    {
        graphicEngine_->drop();
        graphicEngine_ = 0;
    }
}

irr::IrrlichtDevice* Testhelper::getGraphicEngine()
{
    return graphicEngine_;
}

irr::io::IFileSystem* Testhelper::getFileSystem()
{
    return fileSystem_;
}

irr::core::stringc Testhelper::readFile( irr::io::path fileName )
{
    irr::io::IReadFile* file = fileSystem_->createAndOpenFile( fileName );
    irr::u32 size = (irr::u32)( file->getSize() );
    irr::core::array<irr::u8> buffer( size + 4 );
    file->read( buffer.pointer(), size );
    file->drop();
    return buffer.const_pointer();
}

void Testhelper::writeFile( irr::io::path fileName, const irr::core::stringc& content )
{
    irr::io::IWriteFile* file = fileSystem_->createAndWriteFile( fileName, /* append = */ false );
    file->write( content.c_str(), content.size() );
    file->drop();
}

irr::u32 Testhelper::getFileSize( irr::io::path fileName )
{
    irr::io::IReadFile* file = fileSystem_->createAndOpenFile( fileName );
    irr::u32 size = (irr::u32)file->getSize();
    file->drop();
    return size;
}

bool Testhelper::existFile( irr::io::path fileName )
{
    return fileSystem_->existFile( fileName );
}
