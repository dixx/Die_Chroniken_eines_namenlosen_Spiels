add_library(leviathan SHARED
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
target_link_libraries(leviathan "${IRRLICHT_LIBRARY}")
set_target_properties(leviathan PROPERTIES
  LIBRARY_OUTPUT_NAME leviathan
  PREFIX ""
)
install(FILES "${IRRLICHT_BINARY_LIBRARY}" DESTINATION .)
install(TARGETS leviathan RUNTIME DESTINATION .)
