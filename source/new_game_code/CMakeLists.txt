include_directories("${LEVIATHAN_INCLUDE_DIRS}" "${IRRLICHT_INCLUDE_DIRS}")

add_executable(neues_spiel
  GameStatePlay.cpp
  main.cpp
)
target_link_libraries(neues_spiel leviathan)
cotire(neues_spiel)

install(TARGETS neues_spiel DESTINATION .)
