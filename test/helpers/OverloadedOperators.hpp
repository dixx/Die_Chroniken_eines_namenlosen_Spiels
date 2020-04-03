#ifndef OVERLOADED_OPERATORS_H
#define OVERLOADED_OPERATORS_H

#include "../../source/Leviathan/input/Action.h"
#include "irrlicht.h"

// Some of our user-defined types do not have certain operators, because they would only be used in tests.

inline bool operator==(const leviathan::input::Action& lhs, const leviathan::input::Action& rhs) {
    return lhs.id == rhs.id && lhs.isActive == rhs.isActive;
}

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
