#include "../../src/Leviathan/input/EventReceiver.h"
#include "../../src/Leviathan/input/IEventConsumer.h"
#include "catch.hpp"
#include "fakeit.hpp"
#include <input/action.h>

using namespace fakeit;

TEST_CASE("Event Receiver", "[unit]") {
    Mock<leviathan::input::IEventConsumer> consumerMock;
    Fake(Method(consumerMock, onEvent));
    leviathan::input::EventReceiver subject;
    irr::SEvent leftMouseButtonEvent, spaceBarEvent;
    leftMouseButtonEvent.EventType = irr::EET_MOUSE_INPUT_EVENT;
    leftMouseButtonEvent.MouseInput.ButtonStates = irr::EMBSM_LEFT;
    leftMouseButtonEvent.MouseInput.Event = irr::EMIE_LMOUSE_PRESSED_DOWN;
    spaceBarEvent.EventType = irr::EET_KEY_INPUT_EVENT;
    spaceBarEvent.KeyInput.Key = irr::KEY_SPACE;
    spaceBarEvent.KeyInput.PressedDown = false;
    auto isLMBEvent = [](auto other) {
        return other.EventType == irr::EET_MOUSE_INPUT_EVENT && other.MouseInput.Event == irr::EMIE_LMOUSE_PRESSED_DOWN;
    };
    auto isSpacebarEvent = [](auto other) {
        return other.EventType == irr::EET_KEY_INPUT_EVENT && other.KeyInput.Key == irr::KEY_SPACE;
    };

    SECTION("consumers can subscribe to certain event types") {
        subject.subscribe(consumerMock.get(), irr::EET_KEY_INPUT_EVENT);

        SECTION("and receive only subscribed events") {
            subject.OnEvent(leftMouseButtonEvent);
            subject.OnEvent(spaceBarEvent);
            Verify(Method(consumerMock, onEvent).Matching(isSpacebarEvent)).Exactly(Once);
            VerifyNoOtherInvocations(Method(consumerMock, onEvent));
        }

        SECTION("foolproof") {
            subject.subscribe(consumerMock.get(), irr::EET_KEY_INPUT_EVENT);
            subject.OnEvent(leftMouseButtonEvent);
            subject.OnEvent(spaceBarEvent);
            Verify(Method(consumerMock, onEvent).Matching(isSpacebarEvent)).Exactly(Once);
            VerifyNoOtherInvocations(Method(consumerMock, onEvent));
        }
    }

    SECTION("consumers can unsubscribe from certain event types") {
        subject.subscribe(consumerMock.get(), irr::EET_KEY_INPUT_EVENT);
        subject.subscribe(consumerMock.get(), irr::EET_MOUSE_INPUT_EVENT);

        subject.OnEvent(spaceBarEvent);
        subject.OnEvent(leftMouseButtonEvent);
        Verify(Method(consumerMock, onEvent).Matching(isSpacebarEvent)).Exactly(Once);
        Verify(Method(consumerMock, onEvent).Matching(isLMBEvent)).Exactly(Once);
        consumerMock.ClearInvocationHistory();

        subject.unsubscribe(consumerMock.get(), irr::EET_MOUSE_INPUT_EVENT);
        subject.OnEvent(spaceBarEvent);
        subject.OnEvent(leftMouseButtonEvent);
        Verify(Method(consumerMock, onEvent).Matching(isSpacebarEvent)).Exactly(Once);
        VerifyNoOtherInvocations(Method(consumerMock, onEvent));
        consumerMock.ClearInvocationHistory();

        SECTION("foolproof") {
            subject.unsubscribe(consumerMock.get(), irr::EET_MOUSE_INPUT_EVENT);
            subject.OnEvent(spaceBarEvent);
            subject.OnEvent(leftMouseButtonEvent);
            Verify(Method(consumerMock, onEvent).Matching(isSpacebarEvent)).Exactly(Once);
            VerifyNoOtherInvocations(Method(consumerMock, onEvent));
        }
    }

    SECTION("it can handle multiple consumers with multiple subscriptions") {
        Mock<leviathan::input::IEventConsumer> anotherConsumerMock;
        Fake(Method(anotherConsumerMock, onEvent));
        subject.subscribe(consumerMock.get(), irr::EET_KEY_INPUT_EVENT);
        subject.subscribe(anotherConsumerMock.get(), irr::EET_KEY_INPUT_EVENT);
        subject.subscribe(anotherConsumerMock.get(), irr::EET_MOUSE_INPUT_EVENT);

        SECTION("which receive only subscribed events") {
            subject.OnEvent(leftMouseButtonEvent);
            VerifyNoOtherInvocations(Method(consumerMock, onEvent));
            Verify(Method(anotherConsumerMock, onEvent).Matching(isLMBEvent)).Exactly(Once);
            VerifyNoOtherInvocations(Method(consumerMock, onEvent), Method(anotherConsumerMock, onEvent));

            subject.OnEvent(spaceBarEvent);
            Verify(Method(consumerMock, onEvent).Matching(isSpacebarEvent)).Exactly(Once);
            Verify(Method(anotherConsumerMock, onEvent).Matching(isSpacebarEvent)).Exactly(Once);
            VerifyNoOtherInvocations(Method(consumerMock, onEvent), Method(anotherConsumerMock, onEvent));
        }
    }

    SECTION("OnEvent returns success of event procession") {
        REQUIRE_FALSE(subject.OnEvent(spaceBarEvent));

        subject.subscribe(consumerMock.get(), irr::EET_KEY_INPUT_EVENT);
        When(Method(consumerMock, onEvent)).Return(false);
        REQUIRE_FALSE(subject.OnEvent(spaceBarEvent));
        When(Method(consumerMock, onEvent)).Return(true);
        REQUIRE(subject.OnEvent(spaceBarEvent));
    }
}
