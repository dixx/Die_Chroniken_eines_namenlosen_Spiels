include_directories(../source/chroniken_alt "${LEVIATHAN_INCLUDE_DIRS}" "${IRRLICHT_INCLUDE_DIRS}")

add_executable(unit_tests
  ../source/chroniken_alt/Zufall.cpp # TODO will go away when we implement it in the game engine
  helpers/Testhelper.cpp
  helpers/TesthelperLeviathanDevice.cpp
  ActionsTest.cpp
  ConfigurationTest.cpp
  EventReceiverTest.cpp
  GameStateManagerTest.cpp
  GameStateTest.cpp
  LeviathanDeviceTest.cpp
  LoggerTest.cpp
  TimeControlTest.cpp
  TimerTest.cpp
  ZufallTest.cpp
  unit_tests.cpp
)
target_link_libraries(unit_tests "${IRRLICHT_LIBRARY}" leviathan catch fakeit)
cotire(unit_tests)

install(TARGETS unit_tests DESTINATION .)
