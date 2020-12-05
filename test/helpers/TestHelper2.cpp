#include "TestHelper2.h"
#include <cstdlib>
#include <vector>

TestHelper2& TestHelper2::instance() {
    static TestHelper2 instance;
    return instance;
}

irr::IrrlichtDevice* TestHelper2::graphicEngine() {
    return instance().mGraphicEngine;
}

leviathan::core::Logger& TestHelper2::Logger() {
    static leviathan::core::Logger loggerInstance("test.log", leviathan::core::Logger::Level::ALL);
    return loggerInstance;
}

uint32_t TestHelper2::getUniqueId() {
    return instance().mUniqueId++;
}

std::string TestHelper2::readFile(const char* fileName) {
    std::fstream filestream = getFileStream(fileName);
    std::streampos size = getFileSize(filestream, fileName);
    std::vector<char> buffer(static_cast<uint32_t>(size) + 4);
    filestream.read(&buffer[0], static_cast<std::streamsize>(size));
    filestream.close();
    return std::string(buffer.begin(), buffer.end());
}

std::fstream TestHelper2::getFileStream(const char* fileName) {
    std::fstream filestream(fileName, std::fstream::in);
    if (filestream.fail()) {
        filestream.close();
        std::cerr << "Error: Could not open file \"" << fileName << "\"!" << std::endl;
        exit(EXIT_FAILURE);
    }
    return filestream;
}

std::streampos TestHelper2::getFileSize(std::fstream& filestream, const char* fileName) {
    filestream.seekg(0, filestream.end);
    std::streampos size = filestream.tellg();
    filestream.seekg(0, filestream.beg);
    if (size <= 0) {
        filestream.close();
        std::cerr << "Error: Could not get file size of \"" << fileName << "\"!" << std::endl;
        exit(EXIT_FAILURE);
    }
    return size;
}

// void Testhelper::writeFile(const char* fileName, const irr::core::stringc& content) {
//     irr::io::IWriteFile* file = fileSystem_->createAndWriteFile(fileName, /* append = */ false);
//     file->write(content.c_str(), content.size());
//     file->drop();
// }
//
// uint32_t Testhelper::getFileSize(const char* fileName) {
//     irr::io::IReadFile* file = fileSystem_->createAndOpenFile(fileName);
//     const intmax_t result = file->getSize();
//     if (result == -1L) {
//         std::cerr << "Error: Could not get file size of \"" << fileName << "\"!" << std::endl;
//         exit(EXIT_FAILURE);
//     }
//     file->drop();
//     return static_cast<uint32_t>(result);
// }
//
// bool Testhelper::existFile(const char* fileName) {
//     return fileSystem_->existFile(fileName);
// }

TestHelper2::TestHelper2() {
    irr::SIrrlichtCreationParameters params;
    params.DriverType = irr::video::EDT_NULL;
    params.LoggingLevel = irr::ELL_WARNING;
    mGraphicEngine = irr::createDeviceEx(params);
}

TestHelper2::~TestHelper2() {
    if (mGraphicEngine) mGraphicEngine->drop();
}
