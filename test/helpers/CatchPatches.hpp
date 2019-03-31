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
            std::stringstream ss;
            ss << "(" << obj.X << ", " << obj.Y << ")";
            return ss.str();
        }
    };
}

#endif
