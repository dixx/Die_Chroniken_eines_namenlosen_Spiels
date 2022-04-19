/*! \file GroundTile.h
 *  \brief Ein Bodenteil.
 *  \note Bestandteil der Leviathan Engine
 */

#ifndef LEVIATHAN_WORLD_GROUND_TILE_H
#define LEVIATHAN_WORLD_GROUND_TILE_H

#include <video/Vector3D.h>
#include <world/INode3D.h>

namespace irr {
    namespace scene {
        class ISceneManager;
        class IMeshSceneNode;
        class IMesh;
    }
}

namespace leviathan {
    namespace world {
        struct Node3DConfiguration;

        /*! \class GroundTile
         *  \brief Ein Bodenteil.
         */
        class GroundTile : public INode3D {
        public:
            GroundTile(const Node3DConfiguration& tileConfig, irr::scene::ISceneManager* sceneManager);

            ~GroundTile();

            GroundTile(const GroundTile&) = default;
            GroundTile(GroundTile&&) = default;
            GroundTile& operator=(const GroundTile&) = default;
            GroundTile& operator=(GroundTile&&) = default;

            void setDesiredPostition(const video::Position3D& targetPosition) override;

        private:
            irr::scene::ISceneManager* mSceneManager = nullptr;
            video::Position3D mDesiredPosition = video::Position3D();
            irr::scene::IMeshSceneNode* mTileNode = nullptr;

            void transformMesh(irr::scene::IMesh* mesh, const Node3DConfiguration& tileConfig);
            void defineAppearance(const char* textureFileName);
            void addTriangleSelector();
        };
    }
}
#endif
