#include "Randomizer.h"
#include "irrlicht.h"
#include <math.h>

namespace leviathan {
    namespace core {
        void Randomizer::start(const uint32_t seed) {
            seed_ = seed;
            if (seed_ > 100) {
                seed2_ = seed_ / 2 - 1;
                seed3_ = seed2_ / 2 - 3;
                seed4_ = seed3_ / 2 - 8;
            } else {
                seed2_ = seed_ * 2 + 1;
                seed3_ = seed2_ * 2 + 3;
                seed4_ = seed3_ * 2 + 8;
            }
        }

        float Randomizer::getFloat() {
            return (static_cast<float>(getInt()) / static_cast<float>(UINT32_MAX));
        }

        float Randomizer::getFloat(const float min, const float max) {
            if (irr::core::equals(min, max)) // TODO: replace with std methods
                return min;
            return (min > max) ? max + getFloat() * (min - max) : min + getFloat() * (max - min);
        }

        uint32_t Randomizer::getInt() {
            tmp_ = (seed_ ^ (seed_ << 15));
            seed_ = seed2_;
            seed2_ = seed3_;
            seed3_ = seed4_;
            seed4_ = (seed4_ ^ (seed4_ >> 21)) ^ (tmp_ ^ (tmp_ >> 4));
            return seed4_;
        }

        uint32_t Randomizer::getInt(const uint32_t min, const uint32_t max) {
             // TODO: replace irr::core::round() with std methods
            if (min == max) {
                return min;
            } else if (min > max) {
                return max + static_cast<uint32_t>(irr::core::round32(getFloat() * static_cast<float>(min - max)));
            } else {
                return min + static_cast<uint32_t>(irr::core::round32(getFloat() * static_cast<float>(max - min)));
            }
        }
    }
}
