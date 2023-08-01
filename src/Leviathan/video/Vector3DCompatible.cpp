#include "Vector3DCompatible.h"

namespace leviathan {
    namespace video {
        Vector3DCompatible::Vector3DCompatible() : Vector3D() {}

        Vector3DCompatible::Vector3DCompatible(std::initializer_list<float> list) : Vector3D() {
            if (list.size() > 0) x = list.begin()[0];
            if (list.size() > 1) y = list.begin()[1];
            if (list.size() > 2) z = list.begin()[2];
        }

        Vector3DCompatible::Vector3DCompatible(const Vector3DCompatible& other) : Vector3D(other) {}

        Vector3DCompatible::Vector3DCompatible(const Vector3DCompatible&& other) : Vector3D(other) {}

        Vector3DCompatible::Vector3DCompatible(const Vector3D& other) : Vector3D(other) {}

        Vector3DCompatible::Vector3DCompatible(const Vector3D&& other) : Vector3D(other) {}

        Vector3DCompatible::Vector3DCompatible(const irr::core::vector3df& other)
        : Vector3D({other.X, other.Y, other.Z}) {}

        Vector3DCompatible::Vector3DCompatible(const irr::core::vector3df&& other)
        : Vector3D({other.X, other.Y, other.Z}) {}

        Vector3DCompatible& Vector3DCompatible::operator=(const Vector3D& other) {
            x = other.x;
            y = other.y;
            z = other.z;
            return *this;
        }

        Vector3DCompatible& Vector3DCompatible::operator=(const Vector3DCompatible& other) {
            x = other.x;
            y = other.y;
            z = other.z;
            return *this;
        }

        Vector3DCompatible& Vector3DCompatible::operator=(const irr::core::vector3df& other) {
            x = other.X;
            y = other.Y;
            z = other.Z;
            return *this;
        }

        Vector3DCompatible Vector3DCompatible::operator+(const Vector3DCompatible& other) {
            return {x + other.x, y + other.y, z + other.z};
        }

        Vector3DCompatible Vector3DCompatible::operator+(const Vector3D& other) {
            return {x + other.x, y + other.y, z + other.z};
        }

        Vector3DCompatible Vector3DCompatible::operator+(const irr::core::vector3df& other) {
            return {x + other.X, y + other.Y, z + other.Z};
        }

        Vector3DCompatible& Vector3DCompatible::operator+=(const Vector3D& other) {
            x += other.x;
            y += other.y;
            z += other.z;
            return *this;
        }

        Vector3DCompatible& Vector3DCompatible::operator+=(const Vector3DCompatible& other) {
            x += other.x;
            y += other.y;
            z += other.z;
            return *this;
        }

        Vector3DCompatible& Vector3DCompatible::operator+=(const irr::core::vector3df& other) {
            x += other.X;
            y += other.Y;
            z += other.Z;
            return *this;
        }

        Vector3DCompatible Vector3DCompatible::operator-(const Vector3DCompatible& other) {
            return {x - other.x, y - other.y, z - other.z};
        }

        Vector3DCompatible Vector3DCompatible::operator-(const Vector3D& other) {
            return {x - other.x, y - other.y, z - other.z};
        }

        Vector3DCompatible Vector3DCompatible::operator-(const irr::core::vector3df& other) {
            return {x - other.X, y - other.Y, z - other.Z};
        }

        Vector3DCompatible Vector3DCompatible::operator*(float multiplier) {
            return {x * multiplier, y * multiplier, z * multiplier};
        }

        void Vector3DCompatible::rotateXZBy(float angle) {
            irr::core::vector3df intermediate = toIrrlichtVector();
            intermediate.rotateXZBy(angle);
            x = intermediate.X;
            y = intermediate.Y;
            z = intermediate.Z;
        }

        irr::core::vector3df Vector3DCompatible::toIrrlichtVector() const {
            return irr::core::vector3df(x, y, z);
        }
    }
}
