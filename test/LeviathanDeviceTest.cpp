#include <catch.hpp>
#include <fakeit.hpp>
#include <cstdint>
#include <cstdlib>
#include <typeinfo>
#include "irrlicht.h"
#include "../source/Leviathan/LeviathanDevice.h"
#include "helpers/Testhelper.h"
#include "helpers/TesthelperLeviathanDevice.h"

using namespace fakeit;

TEST_CASE("LeviathanDevice supporter") {
    leviathan::LeviathanDevice subject;

    SECTION("it provides instances of usefull tools") {
        REQUIRE(typeid(subject.Logger()) == typeid(leviathan::core::Logger));
        REQUIRE(typeid(subject.TimeControl()) == typeid(leviathan::core::TimeControl));
        REQUIRE(typeid(subject.Configuration()) == typeid(leviathan::core::Configuration));
        REQUIRE(typeid(subject.GameStateManager()) == typeid(leviathan::core::GameStateManager));
        REQUIRE(typeid(subject.Actions()) == typeid(leviathan::input::Actions));
    }
}

TEST_CASE("LeviathanDevice main loop") {
    Testhelper testhelper;
    const irr::io::path configFileName = "testconfigfile.ini";
    testhelper.writeFile(configFileName, "[video]\nmax_fps=100\nscreen_x=5\nscreen_y=5\n");
    TesthelperLeviathanDevice::LeviathanDeviceWithIrrlichtMock subject;
    subject.init(configFileName);
    Mock<irr::ITimer> timerDouble;
    When(Method(timerDouble, getTime)).AlwaysReturn(0);
    Mock<irr::IrrlichtDevice> graphicEngineDouble;
    Fake(Method(graphicEngineDouble, yield));
    Fake(Method(graphicEngineDouble, closeDevice));
    When(Method(graphicEngineDouble, getTimer)).AlwaysReturn(&(timerDouble.get()));
    When(Method(graphicEngineDouble, isWindowActive)).AlwaysReturn(true);
    subject.injectMockedGraphicEngine(graphicEngineDouble.get());
    Mock<leviathan::core::GameState> gameStateDouble;
    Fake(Method(gameStateDouble, update), Method(gameStateDouble, draw));
    subject.GameStateManager().add(gameStateDouble.get(), 42);
    subject.GameStateManager().transitTo(42);

    SECTION("it can be halted") {
        subject.halt();
        Verify(Method(graphicEngineDouble, closeDevice)).Exactly(1_Times);
    }

    SECTION("it should be fair to other apps if inactive") {
        When(Method(graphicEngineDouble, run)).Return(5_Times(true), false);
        When(Method(graphicEngineDouble, isWindowActive)).Return(true, true, false, false, true);
        subject.run();
        Verify(Method(graphicEngineDouble, yield)).Exactly(2_Times);
    }

    SECTION("it should not draw if engine is shut down directly after game state update") {
        When(Method(graphicEngineDouble, run)).Return(true, false);
        subject.run();
        Verify(Method(gameStateDouble, draw)).Exactly(0_Times);
    }

    SECTION("performance tests") {
        uint32_t virtualTime = 0;
        When(Method(timerDouble, getTime)).AlwaysDo([&virtualTime]{ return virtualTime++; });
        When(Method(graphicEngineDouble, run)).AlwaysDo([&virtualTime]{ return virtualTime < 1000; });

        SECTION("without calculation stress") {
            subject.run();
            SECTION("it should draw with a fixed maximum frame rate") {
                Verify(Method(gameStateDouble, draw)).Exactly(100_Times);
                SECTION("and it should update every cycle") {
                    Verify(Method(gameStateDouble, update)).Exactly(100_Times);
                }
            }
        }

        SECTION("with peak load") {
            When(Method(gameStateDouble, draw)).AlwaysDo(
                [&virtualTime]{ if (virtualTime == 3) virtualTime += 800; }
            );
            When(Method(gameStateDouble, update)).AlwaysDo([&virtualTime](...){ virtualTime++; });
            subject.run();
            SECTION("it should draw with a fixed maximum frame rate") {
                Verify(Method(gameStateDouble, draw)).Exactly(100_Times);
                SECTION("and it should update every cycle") {
                    Verify(Method(gameStateDouble, update)).Exactly(100_Times);
                }
            }
        }

        SECTION("with sometimes zero elapsed time") {
            std::srand(42);
            When(Method(timerDouble, getTime)).AlwaysDo(
                [&virtualTime]{ return (std::rand()&1) ? virtualTime : virtualTime++; }
            );
            subject.run();
            SECTION("it should draw with a fixed maximum frame rate") {
                Verify(Method(gameStateDouble, draw)).Exactly(100_Times);
                SECTION("and it should update every cycle") {
                    Verify(Method(gameStateDouble, update)).Exactly(100_Times);
                }
            }
        }

        SECTION("with moderate calculation stress") {
            When(Method(gameStateDouble, draw)).AlwaysDo([&virtualTime]{ virtualTime += 8; });
            When(Method(gameStateDouble, update)).AlwaysDo([&virtualTime](...){ virtualTime++; });
            subject.run();
            SECTION("it should begin to skip frames") {
                Verify(Method(gameStateDouble, draw)).AtLeast(85_Times);
                SECTION("but it should update every cycle") {
                    Verify(Method(gameStateDouble, update)).Exactly(100_Times);
                }
            }
        }

        SECTION("with much calculation stress") {
            When(Method(gameStateDouble, draw)).AlwaysDo([&virtualTime]{ virtualTime += 200; });
            When(Method(gameStateDouble, update)).AlwaysDo([&virtualTime](...){ virtualTime++; });
            subject.run();
            SECTION("it should still try to draw") {
                Verify(Method(gameStateDouble, draw)).AtLeast(5_Times);
                SECTION("and it should try to update many cycles") {
                    Verify(Method(gameStateDouble, update)).AtLeast(40_Times);
                }
            }
        }
    }
}

TEST_CASE("LeviathanDevice exit status") {
    leviathan::LeviathanDevice subject;
    Testhelper testhelper;
    const irr::io::path configFileName = "testconfigfile.ini";
    testhelper.writeFile(configFileName, "[video]\nscreen_x=32\nscreen_y=20\n");

    SECTION("it is 0 if everything went well") {
        REQUIRE(0 == subject.exitStatus());
        subject.init(configFileName);
        REQUIRE(0 == subject.exitStatus());
    }
}
