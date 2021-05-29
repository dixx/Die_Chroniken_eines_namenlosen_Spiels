/*! \file Node3DConfiguration.h
 *  \brief Konfiguration für ein 3D-Objekt.
 *  \note Bestandteil der Leviathan Engine
 */

#ifndef LEVIATHAN_WORLD_NODE3D_CONFIGURATION_H
#define LEVIATHAN_WORLD_NODE3D_CONFIGURATION_H

#include <string>
#include <video/Vector3D.h>

namespace leviathan {
    namespace world {
        /*! \brief Konfiguration für ein 3D-Objekt.
         */
        struct Node3DConfiguration {
            std::string meshFileName;
            video::Position3D position;
            video::Position3D offset;
            video::Rotation3D rotation;
            video::Scale3D scale = {1.f, 1.f, 1.f};
        };
    }
}
#endif
