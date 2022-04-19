#include "Heroes.h"
#include "../world/NodeManager.h"
#include <characters/CharacterConfiguration.h>
#include <characters/IHero.h>

namespace leviathan {
    namespace characters {
        Heroes::Heroes(world::NodeManager& nodeManager) : mNodeManager(nodeManager) {}

        IHero& Heroes::create(const CharacterConfiguration& characterConfig) {
            mHeroes[characterConfig.internalName] = std::make_unique<Hero>(characterConfig, mNodeManager);
            return *mHeroes[characterConfig.internalName];
        }

        void Heroes::activate(const std::string& internalName) {
            if (mHeroes.count(internalName) == 1) mActiveHeroName = std::string(internalName);
        }

        IHero& Heroes::getActiveHero() {
            return *mHeroes[mActiveHeroName];
        }
    }
}
