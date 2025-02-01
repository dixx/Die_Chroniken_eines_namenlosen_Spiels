cmake_minimum_required(VERSION 3.31.0)
include_directories("${PUBLIC_INTERFACES}")

add_executable(neues_spiel
  CameraMover.cpp
  GameStateLoadGame.cpp
  GameStateMainMenu.cpp
  GameStatePlay.cpp
  GameStateShutdown.cpp
  HeroMover.cpp
  main.cpp
  ${PUBLIC_HEADER_FILES}
)
target_link_libraries(neues_spiel leviathan)
cotire(neues_spiel)

install(TARGETS neues_spiel DESTINATION .)
install(FILES
  "${RESOURCES_DIR}/config.yaml"
  "${RESOURCES_DIR}/action_mappings.yaml"
DESTINATION .)
install(FILES
  "${RESOURCES_DIR}/GFX/Mauszeiger.bmp"
  "${RESOURCES_DIR}/GFX/menues1.bmp"
  "${RESOURCES_DIR}/GFX/OBJECTS/sydney.md2"
  "${RESOURCES_DIR}/GFX/sydney.bmp"
  "${RESOURCES_DIR}/GFX/brushed_terrain.png"
  "${RESOURCES_DIR}/GFX/MAP/landscape_river_10.obj"
DESTINATION ./gfx)
