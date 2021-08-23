#include "LeviathanDevice.h"
#include <leviathan.h>

namespace leviathan {
    ILeviathanDevice& createDevice(const char* fileName) {
        static LeviathanDevice instance(fileName);
        return instance;
    }
}
