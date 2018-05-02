cmake_minimum_required(VERSION 3.9.2)
project("Die Chroniken eines namenlosen Spiels")

if(NOT CMAKE_CONFIGURATION_TYPES AND NOT CMAKE_BUILD_TYPE) # TODO check!
  set(CMAKE_BUILD_TYPE Debug)
endif(NOT CMAKE_CONFIGURATION_TYPES AND NOT CMAKE_BUILD_TYPE)

set(CMAKE_INSTALL_PREFIX "${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE}")

# TODO check constants for project root dir instead of using CMAKE_SOURCE_DIR
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake" "${CMAKE_SOURCE_DIR}/cmake/Modules")
set(3RDPARTY_DIR "${CMAKE_SOURCE_DIR}/dependencies")
set(RESOURCES_DIR "${CMAKE_SOURCE_DIR}/dev_media") # TODO (re)move together with chroniken_alt

include(compilerFlags)

find_package(Catch REQUIRED)
find_package(FakeIt REQUIRED)
find_package(IrrKlang REQUIRED)
find_package(Irrlicht REQUIRED)
find_package(Lua REQUIRED)

add_subdirectory(source/Leviathan)
add_subdirectory(source/new_game_code)
add_subdirectory(source/chroniken_alt)
add_subdirectory(test)
