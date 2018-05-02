include_directories(../Leviathan "${IRRLICHT_INCLUDE_DIRS}")

add_executable(neues_spiel
  GameStatePlay.cpp
  main.cpp
)
target_link_libraries(neues_spiel leviathan)
install(TARGETS neues_spiel DESTINATION .)
