#ifndef HELPERS_TESTHELPER_H
#define HELPERS_TESTHELPER_H

#include "irrlicht.h"
#include <cstdint>
#include <string>
#include "../../source/Leviathan/core/Logger.h" // we dogfood our own code ;)
#include "CatchPatches.hpp"

class Testhelper {
public:
    Testhelper();
    ~Testhelper();
    Testhelper(const Testhelper&) = delete;
    void operator=(const Testhelper&) = delete;
    irr::IrrlichtDevice* getGraphicEngine();
    irr::io::IFileSystem* getFileSystem();
    std::string readFile(const char* fileName);
    void writeFile(const char* fileName, const irr::core::stringc& content);
    uint32_t getFileSize(const char* fileName);
    bool existFile(const char* fileName);
    static leviathan::core::Logger& Logger();

private:
    irr::IrrlichtDevice* graphicEngine_ = nullptr;
    irr::io::IFileSystem* fileSystem_ = nullptr;
};

#endif
