cmake_minimum_required (VERSION 3.0)
project (Spiel)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wextra")
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Weverything")
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pedantic")

set(IRRLICHT_DIR ${CMAKE_SOURCE_DIR}/Debug/dependencies/irrlicht-1.8.1)
include_directories(${IRRLICHT_DIR}/include/)
include_directories(${IRRLICHT_DIR}/source/Irrlicht/)
link_directories(${IRRLICHT_DIR}/source/Irrlicht/MacOSX/BD/)

set(IRRKLANG_DIR ${CMAKE_SOURCE_DIR}/Debug/dependencies/irrKlang-1.5.0)
include_directories(${IRRKLANG_DIR}/include/)
link_directories(${IRRKLANG_DIR}/bin/macosx-gcc/)

set(SOURCES
  Basic3DObject.cpp
  BasicHero.cpp
  BasicLifeform.cpp
  BasicStaticObject.cpp
  BufferCullMeshSceneNode.cpp
  Camera.cpp
  Collision.cpp
  Configuration.cpp
  DebugShape.cpp
  DebugShapesManager.cpp
  DebugStatistics.cpp
  Debugwindow.cpp
  Eventreceiver.cpp
  GameFloatControl.cpp
  GameStateManager.cpp
  GenericHelperMethods.cpp
  Ground.cpp
  Hero.cpp
  HeroPunk.cpp
  LoadingScreen.cpp
  Logfile.cpp
  MapTile.cpp
  Mauspfeil.cpp
  ObjectConfiguration.cpp
  ObjectManager.cpp
  ObjectParamsExtractor.cpp
  SaveGames.cpp
  Scripting.cpp
  StateLoadGameContent.cpp
  StateMainMenu.cpp
  StatePlayTheGame.cpp
  StateStartup.cpp
  StateUnloadGameContent.cpp
  Timer.cpp
  TimerManager.cpp
  Ton.cpp
  Vegetation.cpp
  Weather.cpp
  Zufall.cpp
  main.cpp
)

add_executable(spiel MACOSX_BUNDLE ${SOURCES})
set_target_properties(spiel PROPERTIES
  COMPILE_FLAGS "-D_DEBUG_MODE=1"
  LINK_FLAGS "-framework cocoa -framework opengl -framework IOKit"
)
target_link_libraries(spiel lua Irrlicht irrklang)
if (APPLE)
  set_target_properties(spiel PROPERTIES OUTPUT_NAME "Spiel")
endif (APPLE)
