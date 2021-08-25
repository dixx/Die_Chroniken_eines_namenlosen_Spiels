#ifndef OVERLOADED_OPERATORS_H
#define OVERLOADED_OPERATORS_H

#include "IEventReceiver.h"
#include "catch.hpp"
#include <characters/IHero.h>
#include <input/Action.h>
#include <video/Vector3D.h>

// Some of our user-defined types do not have certain operators, because they would only be used in tests.

inline bool operator==(const leviathan::input::Action& lhs, const leviathan::input::Action& rhs) {
    return lhs.id == rhs.id && lhs.isActive == rhs.isActive;
}

inline bool operator==(const leviathan::characters::IHero& lhs, const leviathan::characters::IHero& rhs) {
    return lhs.getInternalName() == rhs.getInternalName();
}

inline bool operator==(const leviathan::video::Vector3D& lhs, const leviathan::video::Vector3D& rhs) {
    return lhs.x == Approx(rhs.x) && lhs.y == Approx(rhs.y) && lhs.z == Approx(rhs.z);
}

// Some of the Irrlicht types do not have certain operators, because they would only be used in tests.

inline bool operator==(const irr::SEvent& lhs, const irr::SEvent& rhs) {
    return lhs.EventType == rhs.EventType;
}

// Some operators in std containers do not find our user-defined types.
// see https://stackoverflow.com/questions/24110928/overload-of-operator-not-found-when-called-from-stdostream-iterator

namespace std {
    inline bool operator==(const leviathan::input::Action& lhs, const leviathan::input::Action& rhs) {
        return lhs.id == rhs.id && lhs.isActive == rhs.isActive;
    }
}

#endif
