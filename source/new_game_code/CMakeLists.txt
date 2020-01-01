include_directories("${LEVIATHAN_INCLUDE_DIRS}" "${IRRLICHT_INCLUDE_DIRS}" "${YAML_INCLUDE_DIRS}")

add_executable(neues_spiel
  GameStateMainMenu.cpp
  GameStatePlay.cpp
  GameStateShutdown.cpp
  main.cpp
)
target_link_libraries(neues_spiel leviathan)
cotire(neues_spiel)

install(TARGETS neues_spiel DESTINATION .)
install(FILES
  "${RESOURCES_DIR}/config.ini"
  "${RESOURCES_DIR}/action_mappings.yaml"
DESTINATION .)
install(FILES
  "${RESOURCES_DIR}/GFX/Mauszeiger.bmp"
DESTINATION ./gfx)
