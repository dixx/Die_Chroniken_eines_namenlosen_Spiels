#ifndef CATCH_PATCHES_H
#define CATCH_PATCHES_H

#include "catch.hpp"
#include "rect.h"
#include "vector2d.h"
#include "vector3d.h"
#include <characters/IHero.h>
#include <input/Action.h>
#include <sstream>
#include <string>
#include <video/Position2D.h>
#include <video/Vector3D.h>

namespace Catch {
    template<>
    struct StringMaker<irr::core::vector2di> {
        static std::string convert(const irr::core::vector2di& obj) {
            std::ostringstream ss;
            ss << "vec(" << obj.X << ", " << obj.Y << ")";
            return ss.str();
        }
    };

    template<>
    struct StringMaker<irr::core::vector3df> {
        static std::string convert(const irr::core::vector3df& obj) {
            std::ostringstream ss;
            ss << "vec(" << obj.X << ", " << obj.Y << ", " << obj.Z << ")";
            return ss.str();
        }
    };

    template<>
    struct StringMaker<leviathan::video::Vector3D> {
        static std::string convert(const leviathan::video::Vector3D& obj) {
            std::ostringstream ss;
            ss << "vec(" << obj.x << ", " << obj.y << ", " << obj.z << ")";
            return ss.str();
        }
    };

    template<>
    struct StringMaker<irr::core::recti> {
        static std::string convert(const irr::core::recti& obj) {
            std::ostringstream ss;
            ss << "rect(" << obj.UpperLeftCorner.X << ", " << obj.UpperLeftCorner.Y << ", " << obj.LowerRightCorner.X
               << ", " << obj.LowerRightCorner.Y << ")";
            return ss.str();
        }
    };
}

class Position2DMatcher : public Catch::MatcherBase<leviathan::video::Position2D> {
    const leviathan::video::Position2D& mOther;

public:
    Position2DMatcher(const leviathan::video::Position2D& other) : mOther(other) {}

    bool match(const leviathan::video::Position2D& pos) const override {
        return pos.x == mOther.x && pos.y == mOther.y;
    }

    virtual std::string describe() const override {
        std::ostringstream ss;
        ss << "is equal to (" << mOther.x << ", " << mOther.y << ")";
        return ss.str();
    }
};

inline Position2DMatcher Position2DEqual(const leviathan::video::Position2D& other) {
    return Position2DMatcher(other);
}

class Vector3DMatcher : public Catch::MatcherBase<leviathan::video::Vector3D> {
    const leviathan::video::Vector3D& mOther;

public:
    Vector3DMatcher(const leviathan::video::Vector3D& other) : mOther(other) {}

    bool match(const leviathan::video::Vector3D& vec) const override {
        return vec.x == Approx(mOther.x) && vec.y == Approx(mOther.y) && vec.z == Approx(mOther.z);
    }

    virtual std::string describe() const override {
        std::ostringstream ss;
        ss << "is equal to (" << mOther.x << ", " << mOther.y << ", " << mOther.z << ")";
        return ss.str();
    }
};

inline Vector3DMatcher Vector3DEqual(const leviathan::video::Vector3D& other) {
    return Vector3DMatcher(other);
}

class HeroMatcher : public Catch::MatcherBase<leviathan::characters::IHero> {
    const leviathan::characters::IHero& mOther;

public:
    HeroMatcher(const leviathan::characters::IHero& other) : mOther(other) {}

    bool match(const leviathan::characters::IHero& pos) const override {
        return pos.getInternalName() == mOther.getInternalName();
    }

    virtual std::string describe() const override {
        std::ostringstream ss;
        ss << "is equal to " << mOther.getInternalName();
        return ss.str();
    }
};

inline HeroMatcher HeroEqual(const leviathan::characters::IHero& other) {
    return HeroMatcher(other);
}

class ActionMatcher : public Catch::MatcherBase<leviathan::input::Action> {
    const leviathan::input::Action& mOther;

public:
    ActionMatcher(const leviathan::input::Action& other) : mOther(other) {}

    bool match(const leviathan::input::Action& action) const override {
        return action.id == mOther.id && action.isActive == mOther.isActive;
    }

    virtual std::string describe() const override {
        std::ostringstream ss;
        ss << "is equal to " << mOther.id << "(" << mOther.isActive << ")";
        return ss.str();
    }
};

inline ActionMatcher ActionEqual(const leviathan::input::Action& other) {
    return ActionMatcher(other);
}

#endif
