#ifndef CATCH_PATCHES_H
#define CATCH_PATCHES_H

#include "catch.hpp"
#include "rect.h"
#include "vector2d.h"
#include "vector3d.h"
#include <sstream>
#include <string>
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

#endif
