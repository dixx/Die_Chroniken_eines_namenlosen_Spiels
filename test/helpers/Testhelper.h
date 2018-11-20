#ifndef HELPERS_TESTHELPER_H
#define HELPERS_TESTHELPER_H

#include "irrlicht.h"
#include <cstdint>

class Testhelper {
public:
    Testhelper();
    ~Testhelper();
    Testhelper(const Testhelper&) = delete;
    void operator=(const Testhelper&) = delete;
    irr::IrrlichtDevice* getGraphicEngine();
    irr::io::IFileSystem* getFileSystem();
    irr::core::stringc readFile(irr::io::path fileName);
    void writeFile(irr::io::path fileName, const irr::core::stringc& content);
    uint32_t getFileSize(irr::io::path fileName);
    bool existFile(irr::io::path fileName);

private:
    irr::IrrlichtDevice* graphicEngine_ = nullptr;
    irr::io::IFileSystem* fileSystem_ = nullptr;
};

#endif
