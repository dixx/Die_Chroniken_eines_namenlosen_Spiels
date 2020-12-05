#ifndef HELPERS_TESTHELPER2_H
#define HELPERS_TESTHELPER2_H

#include "../../source/Leviathan/core/Logger.h"
#include "irrlicht.h"
#include <cstdint>
#include <fstream>
#include <iostream>
#include <string>

class TestHelper2 {
public:
    /*! \brief Singleton instance of the TestHelper2.
     *  \note You don't need to call this. This is called automatically by all methods that need it.
     */
    static TestHelper2& instance();

    TestHelper2(const TestHelper2&) = delete;

    void operator=(const TestHelper2&) = delete;

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

    // void writeFile(const char* fileName, const irr::core::stringc& content);
    // uint32_t getFileSize(const char* fileName);
    // bool existFile(const char* fileName);

private:
    irr::IrrlichtDevice* mGraphicEngine = nullptr;
    uint32_t mUniqueId = 0;

    TestHelper2();
    ~TestHelper2();
    static std::fstream getFileStream(const char* fileName);
    static std::streampos getFileSize(std::fstream& filestream, const char* fileName);
};

#endif
