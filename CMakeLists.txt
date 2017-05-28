cmake_minimum_required(VERSION 2.8)
project(spiel)

if(NOT CMAKE_CONFIGURATION_TYPES AND NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug)
endif(NOT CMAKE_CONFIGURATION_TYPES AND NOT CMAKE_BUILD_TYPE)

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)
set(3RDPARTY_DIR ${CMAKE_SOURCE_DIR}/3rdparty)
set(RESOURCES_DIR ${CMAKE_SOURCE_DIR}/dev_media)
set(TEST_DIR ${CMAKE_SOURCE_DIR}/test)
set(SOURCES_DIR ${CMAKE_SOURCE_DIR}/source)
set(NEW_GAME_SOURCES_DIR ${SOURCES_DIR}/new_game_code)
set(ENGINE_SOURCES_DIR ${SOURCES_DIR}/Leviathan)

include(compilerFlags)

find_package(Catch REQUIRED)
find_package(IrrKlang REQUIRED)
find_package(Irrlicht REQUIRED)
find_package(Lua REQUIRED)
include_directories(
  ${CATCH_INCLUDE_DIRS}
  ${ENGINE_SOURCES_DIR}
  ${IRRKLANG_INCLUDE_DIRS}
  ${IRRLICHT_INCLUDE_DIRS}
  ${LUA_INCLUDE_DIRS}
)
link_directories(${IRRKLANG_DIR}/bin/macosx-gcc/) # TODO only if MacOSX?
link_directories(${IRRLICHT_SOURCES_DIR}/MacOSX/BD/) # TODO only if MacOSX?

set(ENGINE_SOURCES
  ${ENGINE_SOURCES_DIR}/Configuration.cpp
  ${ENGINE_SOURCES_DIR}/GameStateManager.cpp
  ${ENGINE_SOURCES_DIR}/LeviathanDevice.cpp
  ${ENGINE_SOURCES_DIR}/Logger.cpp
  ${ENGINE_SOURCES_DIR}/TimeControl.cpp
  ${ENGINE_SOURCES_DIR}/Timer.cpp
)

set(NEW_GAME_SOURCES
  ${NEW_GAME_SOURCES_DIR}/GameStatePlay
  ${NEW_GAME_SOURCES_DIR}/main.cpp
)

set(SOURCES
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
  ${SOURCES_DIR}/Zufall.cpp
  ${TEST_DIR}/ConfigurationTest.cpp
  ${TEST_DIR}/GameStateManagerTest.cpp
  ${TEST_DIR}/GameStateTest.cpp
  ${TEST_DIR}/IrrlichtDeviceMock.cpp
  ${TEST_DIR}/IrrlichtTimerMock.cpp
  ${TEST_DIR}/LeviathanDeviceTest.cpp
  ${TEST_DIR}/LoggerTest.cpp
  ${TEST_DIR}/Testhelper.cpp
  ${TEST_DIR}/TesthelperGameState.cpp
  ${TEST_DIR}/TesthelperLeviathanDevice.cpp
  ${TEST_DIR}/TimeControlTest.cpp
  ${TEST_DIR}/TimerTest.cpp
  ${TEST_DIR}/ZufallTest.cpp
  ${TEST_DIR}/unit_tests.cpp
)

add_executable(${PROJECT_NAME} MACOSX_BUNDLE ${ENGINE_SOURCES} ${SOURCES})
add_executable(neues_spiel ${ENGINE_SOURCES} ${NEW_GAME_SOURCES})
add_executable(unit_tests ${ENGINE_SOURCES} ${SOURCES_FOR_TESTS})
#set_target_properties(${PROJECT_NAME} PROPERTIES)
target_link_libraries(${PROJECT_NAME} ${IRRLICHT_LIBRARY} ${IRRKLANG_LIBRARY} ${LUA_LIBRARY})
target_link_libraries(neues_spiel ${IRRLICHT_LIBRARY} ${IRRKLANG_LIBRARY} ${LUA_LIBRARY})
target_link_libraries(unit_tests ${IRRLICHT_LIBRARY})
if(APPLE)
  set_target_properties(${PROJECT_NAME} PROPERTIES
    LINK_FLAGS "-framework cocoa -framework opengl -framework IOKit"
    OUTPUT_NAME "Spiel"
  )
endif(APPLE)

# on installation, put everything where it belongs
set(CMAKE_INSTALL_PREFIX ../Debug) # change later
install(TARGETS ${PROJECT_NAME} neues_spiel unit_tests DESTINATION .)
install(DIRECTORY ${RESOURCES_DIR}/GFX ${RESOURCES_DIR}/SFX ${RESOURCES_DIR}/SCRIPTS DESTINATION .)
install(DIRECTORY DESTINATION ./SAVEGAMES)
install(FILES ${RESOURCES_DIR}/chroniken.ico DESTINATION .)

if(${CMAKE_SYSTEM_NAME} MATCHES "Windows") # TODO remove?
  install(FILES
    ${IRRLICHT_BINARY_LIBRARY}
    ${IRRKLANG_BINARY_LIBRARY}
    ${LUA_BINARY_LIBRARY}
    DESTINATION .
  )
endif(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
