#include "Randomizer.h"
#include <math.h>

namespace leviathan {
    namespace core {
        void Randomizer::start(const uint32_t seed) {
            mSeed = seed;
            if (mSeed > 100) {
                mSeed2 = mSeed / 2 - 1;
                mSeed3 = mSeed2 / 2 - 3;
                mSeed4 = mSeed3 / 2 - 8;
            } else {
                mSeed2 = mSeed * 2 + 1;
                mSeed3 = mSeed2 * 2 + 3;
                mSeed4 = mSeed3 * 2 + 8;
            }
        }

        float Randomizer::getFloat() {
            return (static_cast<float>(getInt()) / static_cast<float>(UINT32_MAX));
        }

        float Randomizer::getFloat(const float min, const float max) {
            if (min < max) {
                return min + getFloat() * (max - min);
            } else if (min > max) {
                return max + getFloat() * (min - max);
            } else {
                return min;
            }
        }

        uint32_t Randomizer::getInt() {
            mTemp = (mSeed ^ (mSeed << 15));
            mSeed = mSeed2;
            mSeed2 = mSeed3;
            mSeed3 = mSeed4;
            mSeed4 = (mSeed4 ^ (mSeed4 >> 21)) ^ (mTemp ^ (mTemp >> 4));
            return mSeed4;
        }

        uint32_t Randomizer::getInt(const uint32_t min, const uint32_t max) {
            if (min < max) {
                return min + static_cast<uint32_t>(std::round(getFloat() * static_cast<float>(max - min)));
            } else if (min > max) {
                return max + static_cast<uint32_t>(std::round(getFloat() * static_cast<float>(min - max)));
            } else {
                return min;
            }
        }
    }
}
