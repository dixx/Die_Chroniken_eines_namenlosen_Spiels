/*! \file types.h
 *  \brief Definiert Typen für einfacheren Umgang mit world-Objekten.
 *  \note Bestandteil der Leviathan Engine
 */

#ifndef LEVIATHAN_WORLD_TYPES_H
#define LEVIATHAN_WORLD_TYPES_H

#include "../video/types.h"

namespace leviathan {
    namespace world {

        /*! \brief Hilfsobjekt für Aussehen und Position eines Kartenteils.
         */
        struct GroundTileConfiguration {
            const char* fileName;  //!< Pfad zur Mesh-Datei
            leviathan::video::Position3D position;  //!< Position des Kartenteils
            leviathan::video::Rotation3D rotation;  //!< Rotation des Kartenteils
            leviathan::video::Scale3D scale;  //!< Skalierung des Kartenteils
        };
    }
}

#endif