#include "vector3d.h"
#include <video/Vector3D.h>

namespace leviathan {
    namespace video {
        bool Vector3D::equals(const Vector3D& other, float tolerance) const {
            return irr::core::vector3df(x, y, z).equals({other.x, other.y, other.z}, tolerance);
        }

        void Vector3D::setLength(float length) {
            irr::core::vector3df intermediate(x, y, z);
            intermediate.setLength(length);
            x = intermediate.X;
            y = intermediate.Y;
            z = intermediate.Z;
        }

        Rotation3D Vector3D::getHorizontalAngle() const {
            irr::core::vector3df intermediate = irr::core::vector3df(x, y, z).getHorizontalAngle();
            return {intermediate.X, intermediate.Y, intermediate.Z};
        }

        Vector3D operator+(Vector3D const& lhs, Vector3D const& rhs) {
            return {lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z};
        }

        Vector3D operator-(Vector3D const& lhs, Vector3D const& rhs) {
            return {lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z};
        }
    }
}