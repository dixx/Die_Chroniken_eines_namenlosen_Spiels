#include "Testhelper.h"
#include <iostream>
#include <cstdlib>
#include <vector>

Testhelper::Testhelper()
: graphicEngine_(nullptr),
  fileSystem_(nullptr)
{
    irr::SIrrlichtCreationParameters params;
    params.DriverType = irr::video::EDT_NULL;
    params.LoggingLevel = irr::ELL_WARNING;
    graphicEngine_ = irr::createDeviceEx( params );
    fileSystem_ = graphicEngine_->getFileSystem();
}

Testhelper::~Testhelper()
{
    if ( graphicEngine_ )
    {
        graphicEngine_->drop();
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
    const int32_t result = file->getSize();
    if ( result == -1L )
    {
        std::cerr << "Error: Could not get file size of \"" << fileName.c_str() << "\"!" << std::endl;
        exit( EXIT_FAILURE );
    }
    const uint32_t size = static_cast<uint32_t>( result );
    std::vector<uint8_t> buffer( size );
    file->read( buffer.data(), size );
    file->drop();
    return buffer.data();
}

void Testhelper::writeFile( irr::io::path fileName, const irr::core::stringc& content )
{
    irr::io::IWriteFile* file = fileSystem_->createAndWriteFile( fileName, /* append = */ false );
    file->write( content.c_str(), content.size() );
    file->drop();
}

uint32_t Testhelper::getFileSize( irr::io::path fileName )
{
    irr::io::IReadFile* file = fileSystem_->createAndOpenFile( fileName );
    const int32_t result = file->getSize();
    if ( result == -1L )
    {
        std::cerr << "Error: Could not get file size of \"" << fileName.c_str() << "\"!" << std::endl;
        exit( EXIT_FAILURE );
    }
    file->drop();
    return static_cast<uint32_t>( result );
}

bool Testhelper::existFile( irr::io::path fileName )
{
    return fileSystem_->existFile( fileName );
}
