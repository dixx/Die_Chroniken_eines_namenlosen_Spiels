/*! \file MeshHelper.h
 *  \brief Bietet Hilfsfunktionen für Meshes.
 *  \note Bestandteil der Leviathan Engine
 */

#ifndef LEVIATHAN_VIDEO_MESH_HELPER_H
#define LEVIATHAN_VIDEO_MESH_HELPER_H

namespace irr {
    namespace scene {
        class IMesh;
    }
    namespace video {
        class IVideoDriver;
    }
}

namespace leviathan {
    namespace video {

        //! Hilfsfunktionen für Meshes
        namespace MeshHelper {

            /*! \brief Setzt einen Hinweis an den MeshBuffers, dass diese in den Grafikkartenspeicher geladen werden
             *         sollen. Dies umgeht ständiges Kopieren vom RAM in den VRAM bei Meshes, die sich nicht ändern.
             *  \param mesh: Zeiger auf das statische Mesh
             */
            void pushMeshToVRAM(irr::scene::IMesh* mesh);

            /*! \brief Entfernt die MeshBuffer des Meshes aus dem Grafikkartenspeicher.
             *  \param mesh: Zeiger auf das statische Mesh
             *  \param videoDriver: Zeiger auf den Videotreiber der Graphic Engine
             */
            void removeMeshFromVRAM(irr::scene::IMesh* mesh, irr::video::IVideoDriver* videoDriver);
        }
    }
}

#endif
