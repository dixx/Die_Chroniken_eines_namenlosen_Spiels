/*! \file Decoration.h
 *  \brief Ein rein dekoratives Objekt.
 *  \note Bestandteil der Leviathan Engine
 */

#ifndef LEVIATHAN_WORLD_DECORATION_H
#define LEVIATHAN_WORLD_DECORATION_H

#include <video/Vector3D.h>
#include <world/INode3D.h>

namespace irr {
    namespace scene {
        class ISceneManager;
        class IMeshSceneNode;
    }
}

namespace leviathan {
    namespace video {
        class Textures;
    }

    namespace world {
        struct Node3DConfiguration;

        /*! \class Decoration
         *  \brief Ein rein dekoratives Objekt.
         */
        class Decoration : public INode3D {
        public:
            Decoration(const Node3DConfiguration& tileConfig, video::Textures& textures,
                irr::scene::ISceneManager* sceneManager);

            ~Decoration();

            Decoration(const Decoration&) = default;
            Decoration(Decoration&&) = default;
            Decoration& operator=(const Decoration&) = default;
            Decoration& operator=(Decoration&&) = default;

            void setDesiredPostition(const video::Position3D& targetPosition) override;

        private:
            video::Textures& mTextures;
            irr::scene::ISceneManager* mSceneManager = nullptr;
            video::Position3D mDesiredPosition = video::Position3D();
            irr::scene::IMeshSceneNode* mdecorationNode = nullptr;

            void transformSceneNode(const Node3DConfiguration& tileConfig);
            void defineAppearance(const char* textureFileName);
        };
    }
}
#endif
