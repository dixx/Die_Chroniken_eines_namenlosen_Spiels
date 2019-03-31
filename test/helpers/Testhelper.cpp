#include "Testhelper.h"
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <vector>

Testhelper::Testhelper() {
    irr::SIrrlichtCreationParameters params;
    params.DriverType = irr::video::EDT_NULL;
    params.LoggingLevel = irr::ELL_WARNING;
    graphicEngine_ = irr::createDeviceEx(params);
    fileSystem_ = graphicEngine_->getFileSystem();
}

Testhelper::~Testhelper() {
    if (graphicEngine_)
        graphicEngine_->drop();
}

irr::IrrlichtDevice* Testhelper::getGraphicEngine() {
    return graphicEngine_;
}

irr::io::IFileSystem* Testhelper::getFileSystem() {
    return fileSystem_;
}

std::string Testhelper::readFile(const char* fileName) {
    std::fstream filestream(fileName, std::fstream::in);
    if (filestream.fail()) {
        filestream.close();
        std::cerr << "Error: Could not open file \"" << fileName << "\"!" << std::endl;
        exit(EXIT_FAILURE);
    }
    filestream.seekg (0, filestream.end);
    std::streampos size = filestream.tellg();
    filestream.seekg (0, filestream.beg);
    if (size <= 0) {
        filestream.close();
        std::cerr << "Error: Could not get file size of \"" << fileName << "\"!" << std::endl;
        exit(EXIT_FAILURE);
    }
    std::vector<char> buffer(static_cast<uint32_t>(size) + 4);
    filestream.read(&buffer[0], static_cast<std::streamsize>(size));
    filestream.close();
    return std::string(buffer.begin(), buffer.end());
}

void Testhelper::writeFile(const char* fileName, const irr::core::stringc& content) {
    irr::io::IWriteFile* file = fileSystem_->createAndWriteFile(fileName, /* append = */ false);
    file->write(content.c_str(), content.size());
    file->drop();
}

uint32_t Testhelper::getFileSize(const char* fileName) {
    irr::io::IReadFile* file = fileSystem_->createAndOpenFile(fileName);
    const intmax_t result = file->getSize();
    if (result == -1L) {
        std::cerr << "Error: Could not get file size of \"" << fileName << "\"!" << std::endl;
        exit(EXIT_FAILURE);
    }
    file->drop();
    return static_cast<uint32_t>(result);
}

bool Testhelper::existFile(const char* fileName) {
    return fileSystem_->existFile(fileName);
}

leviathan::core::Logger& Testhelper::Logger() {
    static leviathan::core::Logger singleton("test.log", leviathan::core::Logger::Level::ALL);
    return singleton;
}
