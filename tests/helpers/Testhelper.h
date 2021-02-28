#ifndef HELPERS_TESTHELPER_H
#define HELPERS_TESTHELPER_H

#include "../../source/Leviathan/core/Logger.h"
#include "irrlicht.h"
#include <cstdint>
#include <fstream>
#include <iostream>
#include <string>

class TestHelper {
public:
    /*! \brief Singleton instance of the TestHelper.
     *  \note You don't need to call this. This is called automatically by all methods that need it.
     */
    static TestHelper& instance();

    TestHelper(const TestHelper&) = delete;

    void operator=(const TestHelper&) = delete;

    /*! \brief Singleton instance of the Graphic Engine. Use with caution.
     */
    static irr::IrrlichtDevice* graphicEngine();

    /*! \brief Singleton instance of a Logger.
     */
    static leviathan::core::Logger& Logger();

    /*! \brief A unique ID.
     */
    static uint32_t getUniqueId();

    /*! \brief Read the content of a file into a string.
     */
    static std::string readFile(const char* fileName);

    /*! \brief Determine the size of a file, in bytes.
     */
    static uint32_t getFileSize(const char* fileName);

    /*! \brief Determine if a file exists.
     */
    static bool existFile(const char* fileName);

    /*! \brief Write some text into a file.
     *  \note File will be created if it does not exist, and overwritten otherwise.
     */
    static void writeFile(const char* fileName, const std::string& content);

    /*! \brief Delete a file.
     */
    static void deleteFile(const char* fileName);

private:
    irr::IrrlichtDevice* mGraphicEngine = nullptr;
    uint32_t mUniqueId = 0;

    TestHelper();
    ~TestHelper();
    static std::ifstream getInputFileStream(const char* fileName);
    static std::ofstream getOutputFileStream(const char* fileName);
    static std::streampos getFileSize(std::ifstream& filestream, const char* fileName);
};

#endif
