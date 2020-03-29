#include "../../source/Leviathan/input/Actions.h"
#include "../../source/Leviathan/input/IActionConsumer.h"
#include "../../source/Leviathan/input/IEventProducer.h"
#include "../helpers/Testhelper.h"
#include "catch.hpp"
#include "fakeit.hpp"
#include "irrlicht.h"

using namespace fakeit;

TEST_CASE("Action Mapping", "[unit]") {
    Testhelper testhelper;
    const char* mappingsFileName = "testactionmappings.yml";
    irr::core::stringc content = "---\n"
                                 "- name: talk\n"
                                 "  id: 1\n"
                                 "  description: initiate communication\n"
                                 "  input_mappings:\n"
                                 "    primary:\n"
                                 "      name: left mouse button\n"
                                 "      type: mouse\n"
                                 "      id: 0x01\n"
                                 "    secondary:\n"
                                 "      name: <E>\n"
                                 "      type: keyboard\n"
                                 "      id: 0x45\n"
                                 "- name: enable menu item\n"
                                 "  id: 1001\n"
                                 "  description: enable menu item\n"
                                 "  input_mappings:\n"
                                 "    primary:\n"
                                 "      name: <E>\n"
                                 "      type: keyboard\n"
                                 "      id: 0x45\n"
                                 "- name: attack\n"
                                 "  id: 2\n"
                                 "  description: main hand attack\n"
                                 "  input_mappings:\n"
                                 "- name: select\n"
                                 "  id: 100\n"
                                 "  description: select a menu entry\n"
                                 "  internal: true\n"
                                 "  input_mappings:\n"
                                 "    primary:\n"
                                 "      name: <SPACE>\n"
                                 "      type: keyboard\n"
                                 "      id: 0x20\n";
    testhelper.writeFile(mappingsFileName, content);
    Mock<leviathan::input::IEventProducer> eventBrokerMock;
    Mock<leviathan::input::IActionConsumer> consumerMock;
    Fake(Method(eventBrokerMock, subscribe), Method(eventBrokerMock, unsubscribe), Method(consumerMock, onAction));
    leftMouseButtonEvent.EventType = irr::EET_MOUSE_INPUT_EVENT;
    leftMouseButtonEvent.MouseInput.ButtonStates = irr::EMBSM_LEFT;
    leftMouseButtonEvent.MouseInput.Event = irr::EMIE_LMOUSE_PRESSED_DOWN;
    spaceBarEvent.EventType = irr::EET_KEY_INPUT_EVENT;
    spaceBarEvent.KeyInput.Key = irr::KEY_SPACE;
    spaceBarEvent.KeyInput.PressedDown = false;
    eKeyEvent.EventType = irr::EET_KEY_INPUT_EVENT;
    eKeyEvent.KeyInput.Key = irr::KEY_KEY_E;
    eKeyEvent.KeyInput.PressedDown = true;
    unregisteredKeyEvent.EventType = irr::EET_KEY_INPUT_EVENT;
    unregisteredKeyEvent.KeyInput.Key = irr::KEY_KEY_N;
    enum { TALK = 1, ATTACK, SELECT = 100, ENABLE = 1001 };
    leviathan::input::Actions subject(eventBrokerMock.get(), Testhelper::Logger());

    SECTION("subscribes to an event producer for certain input event types") {
        // FIXME issue with the mock when .Using(subject, ...) instead of .Using(_, ...)
        Verify(Method(eventBrokerMock, subscribe).Using(_, irr::EET_MOUSE_INPUT_EVENT)).Exactly(Once);
        Verify(Method(eventBrokerMock, subscribe).Using(_, irr::EET_KEY_INPUT_EVENT)).Exactly(Once);
        VerifyNoOtherInvocations(eventBrokerMock);
    }

    SECTION("consumers can subscribe to certain actions") {
        subject.subscribe(consumerMock.get(), TALK);

        SECTION("mappings can be loaded from file") {
            subject.onEvent(leftMouseButtonEvent);
            VerifyNoOtherInvocations(Method(consumerMock, onAction));
            subject.loadFromFile(mappingsFileName);
            subject.onEvent(leftMouseButtonEvent);
            Verify(Method(consumerMock, onAction).Using(TALK, true)).Exactly(Once);
            consumerMock.ClearInvocationHistory();

            SECTION("and receive only their subscribed actions") {
                Mock<leviathan::input::IActionConsumer> anotherConsumerMock;
                Fake(Method(anotherConsumerMock, onAction));
                subject.subscribe(consumerMock.get(), ATTACK);
                subject.subscribe(anotherConsumerMock.get(), SELECT);

                subject.onEvent(leftMouseButtonEvent);
                Verify(Method(consumerMock, onAction).Using(TALK, true)).Exactly(Once);
                VerifyNoOtherInvocations(Method(anotherConsumerMock, onAction), Method(consumerMock, onAction));

                subject.onEvent(spaceBarEvent);
                Verify(Method(anotherConsumerMock, onAction).Using(SELECT, false)).Exactly(Once);
                VerifyNoOtherInvocations(Method(consumerMock, onAction), Method(anotherConsumerMock, onAction));
            }

            SECTION("with same input for multiple actions") {
                subject.subscribe(consumerMock.get(), ENABLE);
                subject.onEvent(eKeyEvent);
                Verify(Method(consumerMock, onAction).Using(TALK, true)).Exactly(Once);
                Verify(Method(consumerMock, onAction).Using(ENABLE, true)).Exactly(Once);
            }

            SECTION("consumers can unsubscribe from certain actions") {
                subject.unsubscribe(consumerMock.get(), TALK);
                subject.onEvent(leftMouseButtonEvent);
                VerifyNoOtherInvocations(Method(consumerMock, onAction));
            }
        }
    }

    SECTION("onEvent returns success of event procession") {
        REQUIRE_FALSE(subject.onEvent(leftMouseButtonEvent));
        REQUIRE_FALSE(subject.onEvent(spaceBarEvent));
        REQUIRE_FALSE(subject.onEvent(unregisteredKeyEvent));

        subject.subscribe(consumerMock.get(), TALK);
        subject.loadFromFile(mappingsFileName);
        REQUIRE(subject.onEvent(leftMouseButtonEvent));
        REQUIRE(subject.onEvent(spaceBarEvent));
        REQUIRE_FALSE(subject.onEvent(unregisteredKeyEvent));
    }
}
