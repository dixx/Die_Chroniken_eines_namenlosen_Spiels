#include "LeviathanDevice.h"
#include <leviathan.h>

namespace leviathan {
    ILeviathanDevice& createDevice(const char* configFileName) {
        static LeviathanDevice instance(configFileName);
        return instance;
    }
}
