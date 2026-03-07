include_directories("${LEVIATHAN_INCLUDE_DIRS}" "${IRRLICHT_INCLUDE_DIRS}" "${YAML_INCLUDE_DIRS}")

add_executable(unit_tests
  benchmark/OctTreeBenchmarkTest.cpp
  characters/HeroesTest.cpp
  characters/HeroTest.cpp
  core/ConfigurationTest.cpp
  core/GameStateManagerTest.cpp
  core/LoggerTest.cpp
  core/TimeControlTest.cpp
  core/TimerTest.cpp
  core/RandomizerTest.cpp
  gui/MenuControlTest.cpp
  gui/MousePointerControlTest.cpp
  helpers/CatchPatches.hpp
  helpers/FakeitPatches.hpp
  helpers/TestHelper.cpp
  input/ActionsTest.cpp
  input/EventReceiverTest.cpp
  input/KeyboardEventActionsTest.cpp
  input/MouseEventActionsTest.cpp
  video/CameraTest.cpp
  video/GraphicEngineTest.cpp
  video/TexturesTest.cpp
  video/Vector3DTest.cpp
  video/Vector3DCompatibleTest.cpp
  world/ColliderTest.cpp
  world/GroundTest.cpp
  world/NodeManagerTest.cpp
  LeviathanDeviceTest.cpp
  unit_tests.cpp
  ${PUBLIC_HEADER_FILES}
)
target_link_libraries(unit_tests "${IRRLICHT_LIBRARY}" leviathan catch fakeit)
# We deliberately do _not_ cotire the unit_tests target.
# Catch.hpp has to be included with CATCH_CONFIG_MAIN defined, and
# cotire would build its precompiled header without those macros which
# causes the mysterious "expected class-name" error.  Keeping the
# configuration next to the source is easier than inventing a special
# prefix header just for the tests.
# cotire(unit_tests)

install(TARGETS unit_tests DESTINATION .)
