#include "MeshHelper.h"
#include <cstdint>

namespace leviathan {
    namespace video {
        void MeshHelper::pushMeshToVRAM(irr::scene::IMesh* mesh) {
            mesh->grab();
            uint32_t bufferCount = mesh->getMeshBufferCount();
            for (uint32_t i = 0; i < bufferCount; ++i) {
                irr::scene::IMeshBuffer* buffer = mesh->getMeshBuffer(i);
                buffer->setHardwareMappingHint(irr::scene::EHM_STATIC);
                buffer->setDirty();
                buffer->recalculateBoundingBox();
            }
            mesh->drop();
        }

        void MeshHelper::removeMeshFromVRAM(irr::scene::IMesh* mesh, irr::video::IVideoDriver* videoDriver) {
            mesh->grab();
            uint32_t bufferCount = mesh->getMeshBufferCount();
            for (uint32_t i = 0; i < bufferCount; ++i) {
                irr::scene::IMeshBuffer* buffer = mesh->getMeshBuffer(i);
                buffer->setHardwareMappingHint(irr::scene::EHM_NEVER);
                videoDriver->removeHardwareBuffer(buffer);
                buffer->setDirty();
                buffer->recalculateBoundingBox();
            }
            mesh->drop();
        }
    }
}
