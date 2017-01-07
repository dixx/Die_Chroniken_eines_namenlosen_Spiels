cmake_minimum_required(VERSION 2.8)
project(spiel)

set(SOURCES_DIR ${CMAKE_SOURCE_DIR}/source)
set(TEST_DIR ${CMAKE_SOURCE_DIR}/test)
set(3RDPARTY_DIR ${CMAKE_SOURCE_DIR}/3rdparty)

set(ENGINE_SOURCES_DIR ${SOURCES_DIR}/Leviathan)
include_directories(${ENGINE_SOURCES_DIR})

if(NOT CMAKE_CONFIGURATION_TYPES AND NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug)
endif(NOT CMAKE_CONFIGURATION_TYPES AND NOT CMAKE_BUILD_TYPE)

set(IRRLICHT_DIR ${CMAKE_SOURCE_DIR}/Debug/dependencies/irrlicht-1.8.3)
set(IRRLICHT_INCLUDE_DIR ${IRRLICHT_DIR}/include)
set(IRRLICHT_SOURCES_DIR ${IRRLICHT_DIR}/source/Irrlicht) # this is a workaround for an Irrlicht issue with ShadowVolumeSceneNodes
include_directories(${IRRLICHT_INCLUDE_DIR} ${IRRLICHT_SOURCES_DIR})
link_directories(${IRRLICHT_SOURCES_DIR}/MacOSX/BD/)

set(IRRKLANG_DIR ${CMAKE_SOURCE_DIR}/Debug/dependencies/irrKlang-1.5.0)
set(IRRKLANG_INCLUDE_DIR ${IRRKLANG_DIR}/include)
include_directories(${IRRKLANG_INCLUDE_DIR})
link_directories(${IRRKLANG_DIR}/bin/macosx-gcc/)

set(LUA_DIR ${CMAKE_SOURCE_DIR}/Debug/dependencies/lua-5.2.4)
include_directories(${LUA_DIR}/include/)

set(CATCH_DIR ${3RDPARTY_DIR}/catch) # TODO use https://github.com/philsquared/Catch/blob/master/docs/build-systems.md
include_directories(${CATCH_DIR})

if(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
  set(IRRLICHT_LIBRARY ${IRRLICHT_DIR}/lib/Win32-gcc/libIrrlicht.a)
  set(IRRKLANG_LIBRARY ${IRRKLANG_DIR}/lib/Win32-gcc/libirrKlang.a)
  set(LUA_LIBRARY ${LUA_DIR}/liblua.a) # the one >200kB! If not exist, build it.
endif(${CMAKE_SYSTEM_NAME} MATCHES "Windows")

if(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
  set(IRRLICHT_LIBRARY ${IRRLICHT_DIR}/lib/Linux/libIrrlicht.a GL Xxf86vm X11)
  set(IRRKLANG_LIBRARY ${IRRKLANG_DIR}/bin/linux-gcc-64/libIrrKlang.so)
  set(LUA_LIBRARY lua dl)
endif(${CMAKE_SYSTEM_NAME} MATCHES "Linux")

#if(APPLE)
#endif(APPLE)

set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0 -g3")

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -D_DEBUG_MODE=1") # a switch for additional debug stuff deep in the code
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DNULL=0") # sadly this is required by LUA
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fmessage-length=0")

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -c") # compile, but no linking
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -m32")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wunused -Werror -Wshadow -Wnon-virtual-dtor -Wlong-long -Winline -Wunused-parameter -Wunused-variable -Wuninitialized -Wpointer-arith -Wfloat-equal -Wconversion -Wsign-conversion -Wcast-align")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-aggregate-return")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -isystem\"${IRRLICHT_INCLUDE_DIR}/\" -isystem\"${IRRLICHT_SOURCES_DIR}/\" -isystem\"${IRRKLANG_INCLUDE_DIR}/\"") # to suppress warnings from libs
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Weverything") # TODO try it once in a while
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pedantic") # TODO try it once in a while
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Woverloaded-virtual") # uncovers a bug in Hero, TODO investigate!
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wold-style-cast") # TODO fix occurences!
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Weffc++") # TODO fix occurences! If it runs smoothly, remove -Wnon-virtual-dtor above.

set(ENGINE_SOURCES
  ${ENGINE_SOURCES_DIR}/LeviathanDevice.cpp
  ${ENGINE_SOURCES_DIR}/TimeControl.cpp
  ${ENGINE_SOURCES_DIR}/Timer.cpp
)

set(SOURCES
  ${ENGINE_SOURCES}
  ${SOURCES_DIR}/Basic3DObject.cpp
  ${SOURCES_DIR}/BasicHero.cpp
  ${SOURCES_DIR}/BasicLifeform.cpp
  ${SOURCES_DIR}/BasicStaticObject.cpp
  ${SOURCES_DIR}/BufferCullMeshSceneNode.cpp
  ${SOURCES_DIR}/Camera.cpp
  ${SOURCES_DIR}/Collision.cpp
  ${SOURCES_DIR}/Configuration.cpp
  ${SOURCES_DIR}/DebugShape.cpp
  ${SOURCES_DIR}/DebugShapesManager.cpp
  ${SOURCES_DIR}/DebugStatistics.cpp
  ${SOURCES_DIR}/Debugwindow.cpp
  ${SOURCES_DIR}/Eventreceiver.cpp
  ${SOURCES_DIR}/GameFloatControl.cpp
  ${SOURCES_DIR}/GameStateManager.cpp
  ${SOURCES_DIR}/GenericHelperMethods.cpp
  ${SOURCES_DIR}/Ground.cpp
  ${SOURCES_DIR}/Hero.cpp
  ${SOURCES_DIR}/HeroPunk.cpp
  ${SOURCES_DIR}/LoadingScreen.cpp
  ${SOURCES_DIR}/Logfile.cpp
  ${SOURCES_DIR}/MapTile.cpp
  ${SOURCES_DIR}/Mauspfeil.cpp
  ${SOURCES_DIR}/ObjectConfiguration.cpp
  ${SOURCES_DIR}/ObjectManager.cpp
  ${SOURCES_DIR}/ObjectParamsExtractor.cpp
  ${SOURCES_DIR}/SaveGames.cpp
  ${SOURCES_DIR}/Scripting.cpp
  ${SOURCES_DIR}/StateLoadGameContent.cpp
  ${SOURCES_DIR}/StateMainMenu.cpp
  ${SOURCES_DIR}/StatePlayTheGame.cpp
  ${SOURCES_DIR}/StateStartup.cpp
  ${SOURCES_DIR}/StateUnloadGameContent.cpp
  ${SOURCES_DIR}/TimerManager.cpp
  ${SOURCES_DIR}/Ton.cpp
  ${SOURCES_DIR}/Vegetation.cpp
  ${SOURCES_DIR}/Weather.cpp
  ${SOURCES_DIR}/Zufall.cpp
  ${SOURCES_DIR}/main.cpp
)

set(SOURCES_FOR_TESTS
  ${ENGINE_SOURCES}
  ${SOURCES_DIR}/Zufall.cpp
  ${TEST_DIR}/TimeControlTest.cpp
  ${TEST_DIR}/TimerTest.cpp
  ${TEST_DIR}/ZufallTest.cpp
  ${TEST_DIR}/unit_tests.cpp
)

add_executable(${PROJECT_NAME} MACOSX_BUNDLE ${SOURCES})
add_executable(unit_tests ${SOURCES_FOR_TESTS})
#set_target_properties(${PROJECT_NAME} PROPERTIES)
target_link_libraries(${PROJECT_NAME} ${IRRLICHT_LIBRARY} ${IRRKLANG_LIBRARY} ${LUA_LIBRARY})
target_link_libraries(unit_tests ${IRRLICHT_LIBRARY})
if(APPLE)
  set_target_properties(${PROJECT_NAME} PROPERTIES
    LINK_FLAGS "-framework cocoa -framework opengl -framework IOKit"
    OUTPUT_NAME "Spiel"
  )
endif(APPLE)

# on installation, put everything where it belongs
set(CMAKE_INSTALL_PREFIX ../Debug) # change later
install(TARGETS ${PROJECT_NAME} DESTINATION .)
install(TARGETS unit_tests DESTINATION .)
#install(DIRECTORY ${RESOURCES_DIR} DESTINATION .)
