include_directories("${IRRLICHT_INCLUDE_DIRS}" "${YAML_INCLUDE_DIRS}")

add_library(leviathan SHARED
  Actions.cpp
  Configuration.cpp
  EventReceiver.cpp
  GameStateManager.cpp
  Keyboard.cpp
  LeviathanDevice.cpp
  Logger.cpp
  Mouse.cpp
  TimeControl.cpp
  Timer.cpp
)

target_link_libraries(leviathan "${IRRLICHT_LIBRARY}" "${YAML_LIBRARY}")
set_target_properties(leviathan PROPERTIES
  LIBRARY_OUTPUT_NAME leviathan
  PREFIX ""
)
set(LEVIATHAN_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR} PARENT_SCOPE)
cotire(leviathan)

install(TARGETS leviathan RUNTIME DESTINATION .)
install(FILES "${IRRLICHT_BINARY_LIBRARY}" DESTINATION .)
