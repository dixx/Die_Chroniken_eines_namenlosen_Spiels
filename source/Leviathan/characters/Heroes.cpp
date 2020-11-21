#include "Heroes.h"
#include "Hero.h"

namespace leviathan {
    namespace characters {
        Heroes::Heroes(irr::scene::ISceneManager* sceneManager) : sceneManager_(sceneManager) {}

        Hero& Heroes::create(const std::string& internalName) {
            heroes_[internalName] = std::make_unique<Hero>(internalName, sceneManager_);
            return *heroes_[internalName];
        }

        void Heroes::activate(const std::string& internalName) {
            if (heroes_.count(internalName) == 1) activeHeroName_ = std::string(internalName);
        }

        Hero& Heroes::getActiveHero() {
            return *heroes_[activeHeroName_];
        }
    }
}
