include_directories(../source)

add_executable(unit_tests
  ${ENGINE_SOURCES}
  ../source/Zufall.cpp
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
target_link_libraries(unit_tests ${IRRLICHT_LIBRARY})
file(COPY ${IRRLICHT_BINARY_LIBRARY} DESTINATION .)
