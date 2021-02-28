#include "TestHelper.h"
#include <cstdlib>
#include <stdio.h>
#include <vector>

TestHelper& TestHelper::instance() {
    static TestHelper instance;
    return instance;
}

irr::IrrlichtDevice* TestHelper::graphicEngine() {
    return instance().mGraphicEngine;
}

leviathan::core::Logger& TestHelper::Logger() {
    static leviathan::core::Logger loggerInstance("test.log", leviathan::core::Logger::Level::ALL);
    return loggerInstance;
}

uint32_t TestHelper::getUniqueId() {
    return instance().mUniqueId++;
}

std::string TestHelper::readFile(const char* fileName) {
    std::ifstream filestream = getInputFileStream(fileName);
    std::streampos size = getFileSize(filestream, fileName);
    std::vector<char> buffer(static_cast<uint32_t>(size) + 4);
    filestream.read(&buffer[0], static_cast<std::streamsize>(size));
    filestream.close();
    return std::string(buffer.begin(), buffer.end());
}

uint32_t TestHelper::getFileSize(const char* fileName) {
    std::ifstream filestream = getInputFileStream(fileName);
    std::streampos size = getFileSize(filestream, fileName);
    filestream.close();
    return static_cast<uint32_t>(size);
}

std::ifstream TestHelper::getInputFileStream(const char* fileName) {
    std::ifstream filestream(fileName);
    if (filestream.fail()) {
        filestream.close();
        std::cerr << "Error: Could not open file \"" << fileName << "\"!" << std::endl;
        exit(EXIT_FAILURE);
    }
    return filestream;
}

std::ofstream TestHelper::getOutputFileStream(const char* fileName) {
    std::ofstream filestream(fileName);
    if (filestream.fail()) {
        filestream.close();
        std::cerr << "Error: Could not open file \"" << fileName << "\"!" << std::endl;
        exit(EXIT_FAILURE);
    }
    return filestream;
}

std::streampos TestHelper::getFileSize(std::ifstream& filestream, const char* fileName) {
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

void TestHelper::writeFile(const char* fileName, const std::string& content) {
    std::ofstream filestream = getOutputFileStream(fileName);
    filestream << content;
    filestream.close();
}

bool TestHelper::existFile(const char* fileName) {
    std::ifstream infile(fileName);
    return infile.good();
}

void TestHelper::deleteFile(const char* fileName) {
    remove(fileName);
}

TestHelper::TestHelper() {
    irr::SIrrlichtCreationParameters params;
    params.DriverType = irr::video::EDT_NULL;
    params.LoggingLevel = irr::ELL_WARNING;
    mGraphicEngine = irr::createDeviceEx(params);
}

TestHelper::~TestHelper() {
    if (mGraphicEngine) mGraphicEngine->drop();
}
