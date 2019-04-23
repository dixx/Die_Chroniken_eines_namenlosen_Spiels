#ifndef FAKEIT_PATCHES_H
#define FAKEIT_PATCHES_H

#include "fakeit.hpp"
#include "irrlicht.h"
#include <sstream>
#include <string>

namespace fakeit {
    template<>
    struct Formatter<irr::core::vector2di> {
        static std::string format(const irr::core::vector2di& obj) {
            std::ostringstream ss;
            ss << "vec(" << obj.X << ", " << obj.Y << ")";
            return ss.str();
        }
    };

    template<>
    struct Formatter<irr::core::recti> {
        static std::string format(const irr::core::recti& obj) {
            std::ostringstream ss;
            ss << "rect(" << obj.UpperLeftCorner.X << ", " << obj.UpperLeftCorner.Y << ", " << obj.LowerRightCorner.X
                << ", " << obj.LowerRightCorner.Y << ")";
            return ss.str();
        }
    };

    template<>
    struct Formatter<irr::video::SColor> {
        static std::string format(const irr::video::SColor& obj) {
            std::ostringstream ss;
            ss << "col(" << obj.getRed() << ", " << obj.getGreen() << ", " << obj.getBlue() << ", " << obj.getAlpha()
                << ")";
            return ss.str();
        }
    };
}

#endif
