#include "Heroes.h"
#include "../world/NodeManager.h"
#include <characters/CharacterConfiguration.h>
#include <characters/IHero.h>

namespace leviathan {
    namespace characters {
        Heroes::Heroes(world::NodeManager& nodeManager) : nodeManager_(nodeManager) {}

        IHero& Heroes::create(const CharacterConfiguration& characterConfig) {
            heroes_[characterConfig.internalName] = std::make_unique<Hero>(characterConfig, nodeManager_);
            return *heroes_[characterConfig.internalName];
        }

        void Heroes::activate(const std::string& internalName) {
            if (heroes_.count(internalName) == 1) activeHeroName_ = std::string(internalName);
        }

        IHero& Heroes::getActiveHero() {
            return *heroes_[activeHeroName_];
        }
    }
}
