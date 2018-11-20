#include "../../source/Leviathan/input/EventReceiver.h"
#include "../../source/Leviathan/input/IEventConsumer.h"
#include "catch.hpp"
#include "fakeit.hpp"
#include "irrlicht.h"

using namespace fakeit;

// a hack to make the irr::SEvent structs comparable via == operator, as needed by FakeIt
inline bool operator==(const irr::SEvent& lhs, const irr::SEvent& rhs) {
    return lhs.EventType == rhs.EventType;
}

TEST_CASE("Event Receiver") {
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

    SECTION("consumers can subscribe to certain event types") {
        subject.subscribe(consumerMock.get(), irr::EET_KEY_INPUT_EVENT);

        SECTION("and receive only subscribed events") {
            subject.OnEvent(leftMouseButtonEvent);
            VerifyNoOtherInvocations(Method(consumerMock, onEvent));
            subject.OnEvent(spaceBarEvent);
            Verify(Method(consumerMock, onEvent).Using(spaceBarEvent)).Exactly(Once);
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
            Verify(Method(anotherConsumerMock, onEvent).Using(leftMouseButtonEvent)).Exactly(Once);
            VerifyNoOtherInvocations(Method(consumerMock, onEvent), Method(anotherConsumerMock, onEvent));

            subject.OnEvent(spaceBarEvent);
            Verify(Method(consumerMock, onEvent).Using(spaceBarEvent)).Exactly(Once);
            Verify(Method(anotherConsumerMock, onEvent).Using(spaceBarEvent)).Exactly(Once);
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
