#ifndef _TESTHELPER_HEADER
#define _TESTHELPER_HEADER

#include <irrlicht.h>

class Testhelper
{
public:
    Testhelper();
    ~Testhelper();
    irr::IrrlichtDevice* getGraphicEngine();
    irr::io::IFileSystem* getFileSystem();
    irr::core::stringc readFile( irr::io::path fileName );
    irr::u32 getFileSize( irr::io::path fileName );
    bool existFile( irr::io::path fileName );
private:
    irr::IrrlichtDevice* graphicEngine_;
    irr::io::IFileSystem* fileSystem_;
};

#endif
