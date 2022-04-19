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
  ${PUBLIC_INTERFACES}/leviathan.h
  ${PUBLIC_INTERFACES}/ILeviathanDevice.h
  ${PUBLIC_INTERFACES}/characters/CharacterConfiguration.h
  ${PUBLIC_INTERFACES}/characters/IHero.h
  ${PUBLIC_INTERFACES}/characters/IHeroes.h
  ${PUBLIC_INTERFACES}/core/IConfiguration.h
  ${PUBLIC_INTERFACES}/core/IGameState.h
  ${PUBLIC_INTERFACES}/core/IGameStateManager.h
  ${PUBLIC_INTERFACES}/core/ILogger.h
  ${PUBLIC_INTERFACES}/gui/IMenuControl.h
  ${PUBLIC_INTERFACES}/gui/IMousePointerControl.h
  ${PUBLIC_INTERFACES}/gui/MousePointerConfiguration.h
  ${PUBLIC_INTERFACES}/input/Action.h
  ${PUBLIC_INTERFACES}/input/IActionConsumer.h
  ${PUBLIC_INTERFACES}/input/IActions.h
  ${PUBLIC_INTERFACES}/video/Dimension2D.h
  ${PUBLIC_INTERFACES}/video/ICamera.h
  ${PUBLIC_INTERFACES}/video/IPositionable.h
  ${PUBLIC_INTERFACES}/video/Position2D.h
  ${PUBLIC_INTERFACES}/video/Rectangle2D.h
  ${PUBLIC_INTERFACES}/video/Vector3D.h
  ${PUBLIC_INTERFACES}/world/Collision.h
  ${PUBLIC_INTERFACES}/world/ICollider.h
  ${PUBLIC_INTERFACES}/world/INode3D.h
  ${PUBLIC_INTERFACES}/world/IGround.h
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
