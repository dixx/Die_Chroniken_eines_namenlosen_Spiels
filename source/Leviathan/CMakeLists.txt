include_directories("${IRRLICHT_INCLUDE_DIRS}" "${YAML_INCLUDE_DIRS}")

add_library(leviathan SHARED
  core/Configuration.cpp
  core/GameStateManager.cpp
  core/Logger.cpp
  core/Randomizer.cpp
  core/TimeControl.cpp
  core/Timer.cpp
  gui/Menu.cpp
  gui/MenuControl.cpp
  input/Actions.cpp
  input/EventReceiver.cpp
  input/EventToActionConverter.cpp
  input/MouseEventActions.cpp
  video/MousePointerControl.cpp
  LeviathanDevice.cpp
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
