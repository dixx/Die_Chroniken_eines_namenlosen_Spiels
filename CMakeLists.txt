cmake_minimum_required(VERSION 3.9.2)
project("Die Chroniken eines namenlosen Spiels" VERSION 0.5.1 LANGUAGES CXX)

if(NOT CMAKE_CONFIGURATION_TYPES AND NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug)
endif(NOT CMAKE_CONFIGURATION_TYPES AND NOT CMAKE_BUILD_TYPE)
message("Build mode: ${CMAKE_BUILD_TYPE}")
set(CMAKE_INSTALL_PREFIX "${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE}")
set(CMAKE_INSTALL_MESSAGE LAZY)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake" "${PROJECT_SOURCE_DIR}/cmake/Modules")
set(3RDPARTY_DIR "${PROJECT_SOURCE_DIR}/external")
set(RESOURCES_DIR "${PROJECT_SOURCE_DIR}/data")

set(PUBLIC_INTERFACES "${PROJECT_SOURCE_DIR}/include/Leviathan")
set(PUBLIC_HEADER_FILES
  ${PUBLIC_INTERFACES}/characters/CharacterConfiguration.h
  ${PUBLIC_INTERFACES}/video/Vector3D.h
  ${PUBLIC_INTERFACES}/world/INode3D.h
  ${PUBLIC_INTERFACES}/world/Node3DConfiguration.h
)

include(compilerFlags)
include(cotire)

find_package(Catch REQUIRED)
find_package(FakeIt REQUIRED)
find_package(IrrKlang REQUIRED)
find_package(Irrlicht REQUIRED)
find_package(Lua REQUIRED)
find_package(Yaml REQUIRED)

add_subdirectory(src/leviathan)
add_subdirectory(src/new_game_code)
# add_subdirectory(src/chroniken_alt)
add_subdirectory(tests)
