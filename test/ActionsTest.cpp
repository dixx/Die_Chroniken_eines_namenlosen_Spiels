#include <catch.hpp>
#include <fakeit.hpp>
#include "irrlicht.h"
#include "../source/Leviathan/Actions.h"
#include "helpers/Testhelper.h"

using namespace fakeit;

TEST_CASE("Action Mapping") {
    Testhelper testhelper;
    const irr::io::path mappingsFileName = "testactionmappings.yml";
    irr::core::stringc content = "---\n" \
                                 "- name: talk\n" \
                                 "  id: 1\n" \
                                 "  description: initiate communication\n" \
                                 "  input_mappings:\n" \
                                 "    primary:\n" \
                                 "      name: left mouse button\n" \
                                 "      type: mouse\n" \
                                 "      id: 0x01\n" \
                                 "    secondary:\n" \
                                 "      name: <E>\n" \
                                 "      type: keyboard\n" \
                                 "      id: 0x45\n" \
                                 "- name: attack\n" \
                                 "  id: 2\n" \
                                 "  description: main hand attack\n" \
                                 "  input_mappings:\n" \
                                 "- name: select\n" \
                                 "  id: 100\n" \
                                 "  description: select a menu entry\n" \
                                 "  internal: true\n" \
                                 "  input_mappings:\n" \
                                 "    primary:\n" \
                                 "      name: <SPACE>\n" \
                                 "      type: keyboard\n" \
                                 "      id: 0x20\n";
    testhelper.writeFile(mappingsFileName, content);
    Mock<leviathan::input::IEventProducer> eventBrokerMock;
    Mock<leviathan::input::IActionConsumer> consumerMock;
    Fake(Method(eventBrokerMock, subscribe), Method(consumerMock, onAction));
    irr::SEvent leftMouseButtonEvent, spaceBarEvent;
    leftMouseButtonEvent.EventType = irr::EET_MOUSE_INPUT_EVENT;
    leftMouseButtonEvent.MouseInput.ButtonStates = irr::EMBSM_LEFT;
    leftMouseButtonEvent.MouseInput.Event = irr::EMIE_LMOUSE_PRESSED_DOWN;
    spaceBarEvent.EventType = irr::EET_KEY_INPUT_EVENT;
    spaceBarEvent.KeyInput.Key = irr::KEY_SPACE;
    spaceBarEvent.KeyInput.PressedDown = false;
    enum { TALK = 1, ATTACK, SELECT = 100 };

    SECTION("subscribes to an event producer for certain input event types") {
        leviathan::input::Actions subject(eventBrokerMock.get());
        // FIXME issue with the mock when .Using(subject, ...) instead of .Using(_, ...)
        Verify(Method(eventBrokerMock, subscribe).Using(_, irr::EET_MOUSE_INPUT_EVENT)).Exactly(Once);
        Verify(Method(eventBrokerMock, subscribe).Using(_, irr::EET_KEY_INPUT_EVENT)).Exactly(Once);
    }

    SECTION("consumers can subscribe to certain actions") {
        leviathan::input::Actions subject(eventBrokerMock.get());
        subject.subscribe(consumerMock.get(), TALK);

        SECTION("mappings can be loaded from file") {
            subject.onEvent(leftMouseButtonEvent);
            VerifyNoOtherInvocations(Method(consumerMock, onAction));
            subject.mergeFromFile(mappingsFileName);
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

            SECTION("consumers can unsubscribe from certain actions") {
                subject.unsubscribe(consumerMock.get(), TALK);
                subject.onEvent(leftMouseButtonEvent);
                VerifyNoOtherInvocations(Method(consumerMock, onAction));
            }
        }
        SECTION("action mappings can be changed by the user") {
            SECTION("except for internal actions") {}
        }
    }
}
