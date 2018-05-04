include_directories(
  "${IRRKLANG_INCLUDE_DIRS}"
  "${IRRLICHT_INCLUDE_DIRS}"
  "${LUA_INCLUDE_DIRS}"
  "${LEVIATHAN_INCLUDE_DIRS}"
)
if(APPLE)
  link_directories("${IRRKLANG_DIR}/bin/macosx-gcc/")
  link_directories("${IRRLICHT_SOURCES_DIR}/MacOSX/BD/")
endif(APPLE)

add_executable(chroniken_alt MACOSX_BUNDLE
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
  TimerManager.cpp
  Ton.cpp
  Vegetation.cpp
  Weather.cpp
  Zufall.cpp
  main.cpp
)
target_link_libraries(chroniken_alt "${IRRLICHT_LIBRARY}" "${IRRKLANG_LIBRARY}" "${LUA_LIBRARY}" leviathan)
if(APPLE)
  set_target_properties(chroniken_alt PROPERTIES
    LINK_FLAGS "-framework cocoa -framework opengl -framework IOKit"
    OUTPUT_NAME Chroniken_alt
  )
endif(APPLE)

install(TARGETS chroniken_alt DESTINATION .)
install(FILES "${IRRKLANG_BINARY_LIBRARY}" "${LUA_BINARY_LIBRARY}" DESTINATION .)
install(DIRECTORY "${RESOURCES_DIR}/GFX" "${RESOURCES_DIR}/SFX" "${RESOURCES_DIR}/SCRIPTS" DESTINATION .)
install(DIRECTORY DESTINATION ./SAVEGAMES)
install(FILES "${RESOURCES_DIR}/chroniken.ico" DESTINATION .)
