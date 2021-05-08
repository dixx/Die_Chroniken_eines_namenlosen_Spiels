#include "../../src/Leviathan/video/Vector3DCompatible.h"
#include "catch.hpp"
#include "vector3d.h"
#include <typeinfo>
#include <video/Vector3D.h>

TEST_CASE("Vector3DCompatible", "[unit]") {
    SECTION("construct with defaults") {
        leviathan::video::Vector3DCompatible sample;

        REQUIRE(sample.x == Approx(0.f));
        REQUIRE(sample.y == Approx(0.f));
        REQUIRE(sample.z == Approx(0.f));
    }

    SECTION("construct from values") {
        leviathan::video::Vector3DCompatible sample(11.f, 22.f, 33.f);

        REQUIRE(sample.x == Approx(11.f));
        REQUIRE(sample.y == Approx(22.f));
        REQUIRE(sample.z == Approx(33.f));
    }

    SECTION("construct from initializer list") {
        leviathan::video::Vector3DCompatible sample({11.f, 22.f, 33.f});

        REQUIRE(sample.x == Approx(11.f));
        REQUIRE(sample.y == Approx(22.f));
        REQUIRE(sample.z == Approx(33.f));
    }

    SECTION("construct from incomplete initializer list") {
        leviathan::video::Vector3DCompatible sample({11.f, 22.f});

        REQUIRE(sample.x == Approx(11.f));
        REQUIRE(sample.y == Approx(22.f));
        REQUIRE(sample.z == Approx(0.f));
    }

    SECTION("construct from Vector3D") {
        leviathan::video::Vector3D testVector({12.f, 23.f, 34.f});
        leviathan::video::Vector3DCompatible sample(testVector);

        REQUIRE(sample.x == Approx(12.f));
        REQUIRE(sample.y == Approx(23.f));
        REQUIRE(sample.z == Approx(34.f));
    }

    SECTION("conversion into Irrlicht vector") {
        leviathan::video::Vector3DCompatible sample({1.f, 2.f, 3.f});

        REQUIRE(typeid(sample.toIrrlichtVector()) == typeid(irr::core::vector3df));
        REQUIRE(sample.toIrrlichtVector().X == Approx(1.f));
        REQUIRE(sample.toIrrlichtVector().Y == Approx(2.f));
        REQUIRE(sample.toIrrlichtVector().Z == Approx(3.f));
    }
}
