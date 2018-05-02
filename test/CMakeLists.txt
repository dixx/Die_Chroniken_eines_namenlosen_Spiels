include_directories(../source/chroniken_alt ../source/Leviathan "${IRRLICHT_INCLUDE_DIRS}")

add_executable(unit_tests
  ../source/chroniken_alt/Zufall.cpp # TODO will go away when we implement it in the game engine
  helpers/Testhelper.cpp
  helpers/TesthelperLeviathanDevice.cpp
  ConfigurationTest.cpp
  GameStateManagerTest.cpp
  GameStateTest.cpp
  KeyboardTest.cpp
  LeviathanDeviceTest.cpp
  LoggerTest.cpp
  MouseTest.cpp
  TimeControlTest.cpp
  TimerTest.cpp
  ZufallTest.cpp
  unit_tests.cpp
)
target_link_libraries(unit_tests "${IRRLICHT_LIBRARY}" leviathan)
install(TARGETS unit_tests DESTINATION .)
