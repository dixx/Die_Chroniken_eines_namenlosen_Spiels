#include "catch.hpp"
#include <video/Vector3D.h>

TEST_CASE("Vector3D", "[unit]") {
    SECTION(".equals") {
        leviathan::video::Vector3D sample = {1.0f, 2.0f, 3.0f};

        REQUIRE(sample.equals({1.0f, 2.0f, 3.0f}));
        REQUIRE(sample.equals({1.0000001f, 2.0000001f, 3.0000001f}));
        REQUIRE_FALSE(sample.equals({1.0000002f, 2.0000002f, 3.0000002f}));
        REQUIRE(sample.equals({1.2f, 2.25f, 2.8f}, 0.3f));
    }

    SECTION(".setLength", "[unit]") {
        leviathan::video::Vector3D sample = {1.0f, 1.0f, 1.0f};
        sample.setLength(10.0f);

        REQUIRE(sample.equals({5.773f, 5.773f, 5.773f}, 0.001f));
    }

    SECTION(".getHorizontalAngle", "[unit]") {
        leviathan::video::Vector3D sample = {1.0f, 0.0f, 1.0f};

        REQUIRE(sample.getHorizontalAngle().equals({0.0f, 45.0f, 0.0f}));
    }
}
