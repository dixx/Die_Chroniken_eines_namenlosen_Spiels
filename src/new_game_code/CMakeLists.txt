include_directories("${PUBLIC_INTERFACES}")

add_executable(neues_spiel
  GameStateLoadGame.cpp
  GameStateMainMenu.cpp
  GameStatePlay.cpp
  GameStateShutdown.cpp
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
  "${RESOURCES_DIR}/GFX/landtest.png"
  "${RESOURCES_DIR}/GFX/MAP/linksUnten.3ds"
DESTINATION ./gfx)
