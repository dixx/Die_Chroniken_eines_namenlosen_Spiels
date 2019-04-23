include_directories("${LEVIATHAN_INCLUDE_DIRS}" "${IRRLICHT_INCLUDE_DIRS}")

add_executable(unit_tests
  core/ConfigurationTest.cpp
  core/GameStateManagerTest.cpp
  core/LoggerTest.cpp
  core/TimeControlTest.cpp
  core/TimerTest.cpp
  core/RandomizerTest.cpp
  helpers/CatchPatches.hpp
  helpers/FakeitPatches.hpp
  helpers/Testhelper.cpp
  helpers/TesthelperLeviathanDevice.cpp
  input/ActionsTest.cpp
  input/EventReceiverTest.cpp
  video/MousePointerControlTest.cpp
  LeviathanDeviceTest.cpp
  unit_tests.cpp
)
target_link_libraries(unit_tests "${IRRLICHT_LIBRARY}" leviathan catch fakeit)
cotire(unit_tests)

install(TARGETS unit_tests DESTINATION .)
