#include "Vector3DCompatible.h"

namespace leviathan {
    namespace video {
        Vector3DCompatible::Vector3DCompatible() : Vector3D() {}

        Vector3DCompatible::Vector3DCompatible(std::initializer_list<float> list) : Vector3D() {
            if (list.size() > 0) x = list.begin()[0];
            if (list.size() > 1) y = list.begin()[1];
            if (list.size() > 2) z = list.begin()[2];
        }

        Vector3DCompatible::Vector3DCompatible(float ax, float ay, float az) : Vector3D({ax, ay, az}) {}

        Vector3DCompatible::Vector3DCompatible(const Vector3DCompatible& other) : Vector3D(other) {}

        Vector3DCompatible::Vector3DCompatible(const Vector3DCompatible&& other) : Vector3D(other) {}

        Vector3DCompatible::Vector3DCompatible(const Vector3D& other) : Vector3D(other) {}

        Vector3DCompatible::Vector3DCompatible(const Vector3D&& other) : Vector3D(other) {}

        irr::core::vector3df Vector3DCompatible::toIrrlichtVector() const {
            return irr::core::vector3df(x, y, z);
        }
    }
}
