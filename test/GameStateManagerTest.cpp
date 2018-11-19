#include <catch.hpp>
#include <fakeit.hpp>
#include "../source/Leviathan/GameState.h"
#include "../source/Leviathan/GameStateManager.h"

using namespace fakeit;

TEST_CASE("GameStateManager: add game states") {
    leviathan::core::GameStateManager subject;
    Mock<leviathan::core::GameState> startDouble, playDouble, stopDouble;
    Fake(Method(startDouble, update), Method(startDouble, draw));
    Fake(Method(playDouble, update), Method(playDouble, draw));
    Fake(Method(stopDouble, update), Method(stopDouble, draw));
    leviathan::core::GameState &start = startDouble.get(), &play = playDouble.get(), &stop = stopDouble.get();
    enum { STATE_START = 1, STATE_PLAY, STATE_STOP };
    subject.add(start, STATE_START);
    subject.add(play, STATE_PLAY);
    REQUIRE(subject.getGameStateCount() == 2);

    SECTION("indexes are just numbers") {
        subject.add(stop, 17);
        REQUIRE(subject.getGameStateCount() == 3);
    }

    SECTION("indexes are unique, states are not, and the manager is not whiny about it") {
        subject.add(start, STATE_START);
        REQUIRE(subject.getGameStateCount() == 2);
        subject.add(start, 4);
        REQUIRE(subject.getGameStateCount() == 3);
        subject.add(play, STATE_START);
        REQUIRE(subject.getGameStateCount() == 3);
    }
}

TEST_CASE("GameStateManager: transit between game states") {
    leviathan::core::GameStateManager subject;
    Mock<leviathan::core::GameState> startDouble, playDouble, pauseDouble, optionsDouble;
    Fake(Method(startDouble, update), Method(startDouble, draw));
    Fake(Method(playDouble, update), Method(playDouble, draw));
    Fake(Method(pauseDouble, update), Method(pauseDouble, draw));
    Fake(Method(optionsDouble, update), Method(optionsDouble, draw));
    leviathan::core::GameState &start = startDouble.get(), &play = playDouble.get(), &pause = pauseDouble.get(),
            &options = optionsDouble.get();
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
}

TEST_CASE("GameStateManager: update and draw active game states") {
    leviathan::core::GameStateManager subject;
    Mock<leviathan::core::GameState> startDouble, playDouble, pauseDouble;
    Fake(Method(startDouble, update), Method(startDouble, draw));
    Fake(Method(playDouble, update), Method(playDouble, draw));
    Fake(Method(pauseDouble, update), Method(pauseDouble, draw));
    leviathan::core::GameState &start = startDouble.get(), &play = playDouble.get(), &pause = pauseDouble.get();
    enum { STATE_START = 1, STATE_PLAY, STATE_PAUSE };
    subject.add(start, STATE_START);
    subject.add(play, STATE_PLAY);
    subject.add(pause, STATE_PAUSE);

    SECTION("it updates and draws the active state") {
        subject.transitTo(STATE_START);
        subject.draw();
        subject.update(1.1f);
        Verify(Method(startDouble, draw)).Once();
        Verify(Method(startDouble, update).Using(1.1f)).Once();

        SECTION("and only the active state is drawn and updated") {
            subject.transitTo(STATE_PLAY);
            subject.transitTo(STATE_PAUSE);
            subject.draw();
            subject.update(23.456f);
            VerifyNoOtherInvocations(Method(startDouble, draw));
            VerifyNoOtherInvocations(Method(startDouble, update));
            Verify(Method(playDouble, draw)).Exactly(0_Times);
            Verify(Method(playDouble, update)).Exactly(0_Times);
            Verify(Method(pauseDouble, draw)).Once();
            Verify(Method(pauseDouble, update).Using(23.456f)).Once();
        }
    }
}
