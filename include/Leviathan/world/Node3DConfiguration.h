/*! \file Node3DConfiguration.h
 *  \brief Konfiguration für ein 3D-Objekt.
 *  \note Bestandteil der Leviathan Engine
 */

#ifndef LEVIATHAN_PUBLIC_INTERFACES_WORLD_NODE3DCONFIGURATION_H
#define LEVIATHAN_PUBLIC_INTERFACES_WORLD_NODE3DCONFIGURATION_H

#include <string>
#include <video/Vector3D.h>

namespace leviathan {
    namespace world {
        /*! \brief Konfiguration für ein 3D-Objekt.
         */
        struct Node3DConfiguration {
            std::string meshFileName = "";
            std::string textureFileName = "";
            video::Position3D position = {0.f, 0.f, 0.f};
            video::Position3D offset = {0.f, 0.f, 0.f};
            video::Rotation3D rotation = {0.f, 0.f, 0.f};
            video::Scale3D scale = {1.f, 1.f, 1.f};
        };
    }
}
#endif
