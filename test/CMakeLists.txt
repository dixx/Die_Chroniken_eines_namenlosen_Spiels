include_directories(../source/chroniken_alt "${LEVIATHAN_INCLUDE_DIRS}" "${IRRLICHT_INCLUDE_DIRS}")

add_executable(unit_tests
  ../source/chroniken_alt/Zufall.cpp # TODO will go away when we implement it in the game engine
  core/ConfigurationTest.cpp
  core/GameStateManagerTest.cpp
  core/LoggerTest.cpp
  core/TimeControlTest.cpp
  core/TimerTest.cpp
  core/RandomizerTest.cpp
  helpers/Testhelper.cpp
  helpers/TesthelperLeviathanDevice.cpp
  input/ActionsTest.cpp
  input/EventReceiverTest.cpp
  LeviathanDeviceTest.cpp
  unit_tests.cpp
)
target_link_libraries(unit_tests "${IRRLICHT_LIBRARY}" leviathan catch fakeit)
cotire(unit_tests)

install(TARGETS unit_tests DESTINATION .)
