#include "../../source/Leviathan/core/GameStateManager.h"
#include "../../source/Leviathan/core/IGameState.h"
#include "../helpers/Testhelper.h"
#include "catch.hpp"
#include "fakeit.hpp"
#include <stdexcept>

using namespace fakeit;

TEST_CASE("GameStateManager: add game states", "[unit]") {
    leviathan::core::GameStateManager subject(Testhelper::Logger());
    Mock<leviathan::core::IGameState> startMock, playMock, stopMock;
    Fake(Method(startMock, update), Method(startMock, draw), Method(startMock, setActive),
        Method(startMock, setInactive));
    Fake(Method(playMock, update), Method(playMock, draw), Method(playMock, setActive), Method(playMock, setInactive));
    Fake(Method(stopMock, update), Method(stopMock, draw), Method(stopMock, setActive), Method(stopMock, setInactive));
    leviathan::core::IGameState &start = startMock.get(), &play = playMock.get(), &stop = stopMock.get();
    enum { STATE_START = 1, STATE_PLAY, STATE_STOP };
    subject.add(start, STATE_START);
    subject.add(play, STATE_PLAY);

    SECTION("indexes are just numbers") {
        subject.add(stop, 17);
        subject.transitTo(17);
        REQUIRE(subject.getActiveStateID() == 17);
    }

    SECTION("existing indexes are not overwritten") {
        subject.add(start, STATE_START);
        subject.transitTo(STATE_START);
        REQUIRE(subject.getActiveStateID() == STATE_START);
        subject.add(play, STATE_START);
        subject.transitTo(STATE_START);
        REQUIRE(subject.getActiveStateID() == STATE_START);
        subject.draw();
        Verify(Method(startMock, draw)).Once();
        Verify(Method(playMock, draw)).Exactly(0_Times);
    }

    SECTION("states can be added more than once with different index") {
        subject.add(start, 4);
        subject.transitTo(4);
        REQUIRE(subject.getActiveStateID() == 4);
    }

    SECTION("internal ID is not allowed") {
        REQUIRE_THROWS_AS(subject.add(start, 0xffffffff), std::invalid_argument);
    }
}

TEST_CASE("GameStateManager: transit between game states", "[unit]") {
    leviathan::core::GameStateManager subject(Testhelper::Logger());
    Mock<leviathan::core::IGameState> startMock, playMock, pauseMock, optionsMock;
    Fake(Method(startMock, update), Method(startMock, draw), Method(startMock, setActive),
        Method(startMock, setInactive));
    Fake(Method(playMock, update), Method(playMock, draw), Method(playMock, setActive), Method(playMock, setInactive));
    Fake(Method(pauseMock, update), Method(pauseMock, draw), Method(pauseMock, setActive),
        Method(pauseMock, setInactive));
    Fake(Method(optionsMock, update), Method(optionsMock, draw), Method(optionsMock, setActive),
        Method(optionsMock, setInactive));
    leviathan::core::IGameState &start = startMock.get(), &play = playMock.get(), &pause = pauseMock.get(),
                                &options = optionsMock.get();
    enum { STATE_START = 1, STATE_PLAY, STATE_PAUSE, STATE_OPTIONS };
    subject.add(start, STATE_START);
    subject.add(options, STATE_OPTIONS);
    subject.add(pause, STATE_PAUSE);
    subject.add(play, STATE_PLAY);

    SECTION("it activates the requested state if transit to state that is not on the stack") {
        subject.transitTo(STATE_START);
        REQUIRE(subject.getActiveStateID() == STATE_START);
        subject.transitTo(STATE_PLAY);
        REQUIRE(subject.getActiveStateID() == STATE_PLAY);
    }
    SECTION("it activates the requested state if transit to state that is second place of stack") {
        subject.transitTo(STATE_START);
        subject.transitTo(STATE_OPTIONS);
        subject.transitTo(STATE_PLAY);
        subject.transitTo(STATE_PAUSE);
        subject.transitTo(STATE_PLAY);
        REQUIRE(subject.getActiveStateID() == STATE_PLAY);
    }
    SECTION("it changes nothing if transit to state that is on top of stack") {
        subject.transitTo(STATE_START);
        subject.transitTo(STATE_START);
        REQUIRE(subject.getActiveStateID() == STATE_START);
        subject.transitTo(STATE_PLAY);
        subject.transitTo(STATE_PLAY);
        REQUIRE(subject.getActiveStateID() == STATE_PLAY);
    }
    SECTION("it changes nothing if transit to state that is further down the stack") {
        subject.transitTo(STATE_START);
        subject.transitTo(STATE_PLAY);
        subject.transitTo(STATE_PAUSE);
        subject.transitTo(STATE_START);
        REQUIRE(subject.getActiveStateID() == STATE_PAUSE);
    }
    SECTION("it ignores unknown states") {
        subject.transitTo(STATE_START);
        subject.transitTo(42);
        REQUIRE(subject.getActiveStateID() == STATE_START);
    }
    SECTION("it calls activation hooks on the states") {
        subject.transitTo(STATE_START);
        startMock.ClearInvocationHistory();

        subject.transitTo(STATE_PLAY);
        Verify(Method(startMock, setActive)).Exactly(0_Times);
        Verify(Method(startMock, setInactive)).Once();
        Verify(Method(playMock, setActive)).Once();
        Verify(Method(playMock, setInactive)).Exactly(0_Times);
    }
}

TEST_CASE("GameStateManager: update and draw active game states", "[unit]") {
    leviathan::core::GameStateManager subject(Testhelper::Logger());
    Mock<leviathan::core::IGameState> startMock, playMock, pauseMock;
    Fake(Method(startMock, update), Method(startMock, draw), Method(startMock, setActive),
        Method(startMock, setInactive));
    Fake(Method(playMock, update), Method(playMock, draw), Method(playMock, setActive), Method(playMock, setInactive));
    Fake(Method(pauseMock, update), Method(pauseMock, draw), Method(pauseMock, setActive),
        Method(pauseMock, setInactive));
    leviathan::core::IGameState &start = startMock.get(), &play = playMock.get(), &pause = pauseMock.get();
    enum { STATE_START = 1, STATE_PLAY, STATE_PAUSE };
    subject.add(start, STATE_START);
    subject.add(play, STATE_PLAY);
    subject.add(pause, STATE_PAUSE);

    SECTION("it updates and draws the active state") {
        subject.transitTo(STATE_START);
        subject.draw();
        subject.update(1.1f);
        Verify(Method(startMock, draw)).Once();
        Verify(Method(startMock, update).Using(1.1f)).Once();

        SECTION("and only the active state is drawn and updated") {
            subject.transitTo(STATE_PLAY);
            subject.transitTo(STATE_PAUSE);
            subject.draw();
            subject.update(23.456f);
            VerifyNoOtherInvocations(Method(startMock, draw));
            VerifyNoOtherInvocations(Method(startMock, update));
            Verify(Method(playMock, draw)).Exactly(0_Times);
            Verify(Method(playMock, update)).Exactly(0_Times);
            Verify(Method(pauseMock, draw)).Once();
            Verify(Method(pauseMock, update).Using(23.456f)).Once();
        }
    }
}
