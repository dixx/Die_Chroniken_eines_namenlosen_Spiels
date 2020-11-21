#ifndef CATCH_PATCHES_H
#define CATCH_PATCHES_H

#include "catch.hpp"
#include "irrlicht.h"
#include <sstream>
#include <string>

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
