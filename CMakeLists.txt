cmake_minimum_required(VERSION 2.8)
project(Spiel)

if(NOT CMAKE_CONFIGURATION_TYPES AND NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug)
endif(NOT CMAKE_CONFIGURATION_TYPES AND NOT CMAKE_BUILD_TYPE)

set(IRRLICHT_DIR ${CMAKE_SOURCE_DIR}/Debug/dependencies/irrlicht-1.8.3)
include_directories(${IRRLICHT_DIR}/include/ ${IRRLICHT_DIR}/source/Irrlicht/)
link_directories(${IRRLICHT_DIR}/source/Irrlicht/MacOSX/BD/)

set(IRRKLANG_DIR ${CMAKE_SOURCE_DIR}/Debug/dependencies/irrKlang-1.5.0)
include_directories(${IRRKLANG_DIR}/include/)
link_directories(${IRRKLANG_DIR}/bin/macosx-gcc/)

set(LUA_DIR ${CMAKE_SOURCE_DIR}/Debug/dependencies/lua-5.2.4)
include_directories(${LUA_DIR}/include/)

if(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
  set(IRRLICHT_LIBRARY ${IRRLICHT_DIR}/lib/Win32-gcc/libIrrlicht.a)
  set(IRRKLANG_LIBRARY ${IRRKLANG_DIR}/lib/Win32-gcc/libirrKlang.a)
  set(LUA_LIBRARY ${LUA_DIR}/lib/liblua52.a)
endif(${CMAKE_SYSTEM_NAME} MATCHES "Windows")

if(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
  set(IRRLICHT_LIBRARY ${IRRLICHT_DIR}/lib/Linux/libIrrlicht.a GL Xxf86vm X11)
  set(IRRKLANG_LIBRARY ${IRRKLANG_DIR}/lib/Win32-gcc/libirrKlang.a)
  set(LUA_LIBRARY lua dl)
endif(${CMAKE_SYSTEM_NAME} MATCHES "Linux")

#if(APPLE)
#endif(APPLE)

set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0 -g3")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -D_DEBUG_MODE=1") # switch for additional debug stuff deep in the code
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DNULL=0") # sadly this is required by LUA
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -c") # compile, but no linking
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fmessage-length=0")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -m32") # let's enable this only if we really need it
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror -Wno-aggregate-return -Wlong-long -Winline -Wunreachable-code -Wunused -Wunused-function -Wunused-label -Wunused-parameter -Wunused-value -Wunused-variable -Wuninitialized -Wreturn-type -Wparentheses -Wpointer-arith -Wmissing-braces -Wfloat-equal -Wconversion -Wcast-align")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -isystem\"${IRRLICHT_DIR}/include/\" -isystem\"${IRRLICHT_DIR}/source/Irrlicht/\" -isystem\"${IRRKLANG_DIR}/include/\"")
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Weverything")
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pedantic")

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
set(SOURCES_FOR_TESTS unit_tests.cpp)

add_executable(spiel MACOSX_BUNDLE ${SOURCES})
add_executable(unit_tests ${SOURCES_FOR_TESTS})
#set_target_properties(spiel PROPERTIES)
target_link_libraries(spiel ${IRRLICHT_LIBRARY} ${IRRKLANG_LIBRARY} ${LUA_LIBRARY})
#target_link_libraries(unit_tests ${IRRLICHT_LIBRARY})
if(APPLE)
  set_target_properties(spiel PROPERTIES
    LINK_FLAGS "-framework cocoa -framework opengl -framework IOKit"
    OUTPUT_NAME "Spiel"
  )
endif(APPLE)

# on installation, put everything where it belongs
set(CMAKE_INSTALL_PREFIX ../Debug) # change later
install(TARGETS spiel DESTINATION .)
install(TARGETS unit_tests DESTINATION .)
#install(DIRECTORY ${RESOURCES_DIR} DESTINATION .)
