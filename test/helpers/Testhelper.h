#ifndef _TESTHELPER_HEADER
#define _TESTHELPER_HEADER

#include "irrlicht.h"
#include <cstdint>

class Testhelper
{
public:
    Testhelper();
    ~Testhelper();
    irr::IrrlichtDevice* getGraphicEngine();
    irr::io::IFileSystem* getFileSystem();
    irr::core::stringc readFile(irr::io::path fileName);
    void writeFile(irr::io::path fileName, const irr::core::stringc& content);
    uint32_t getFileSize(irr::io::path fileName);
    bool existFile(irr::io::path fileName);
private:
    irr::IrrlichtDevice* graphicEngine_;
    irr::io::IFileSystem* fileSystem_;
    Testhelper(const Testhelper&);
    void operator=(const Testhelper&);
};

#endif
