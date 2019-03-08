#ifndef PUGGO_TRANSFORM_HPP
#define PUGGO_TRANSFORM_HPP
#define GLM_ENABLE_EXPERIMENTAL

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/norm.hpp>
#include <glm/gtx/dual_quaternion.hpp>

using namespace glm;

namespace puggo {
    class Transform {
    public:
        Transform(
            const fdualquat& translationAndRotation = fdualquat(fquat(1.f, 0.f, 0.f, 0.f), vec3(0.f, 0.f, 0.f)),
            const vec3& scale = vec3(1.f, 1.f, 1.f)
        );

        Transform(const Transform& transform) noexcept;

        Transform(Transform&& transform) noexcept;

        Transform operator*(const Transform& other) const noexcept;
        Transform& operator=(const Transform& other) noexcept;
        Transform& operator=(Transform&& other) noexcept;
        bool operator==(const Transform& other) noexcept;

        mat4 getMatrix(void) const noexcept;
        mat4 getInverseMatrix(void) const noexcept;
        Transform getInverse(void) const noexcept;
        vec3 getXUnitVector(void) const noexcept;
        vec3 getYUnitVector(void) const noexcept;
        vec3 getZUnitVector(void) const noexcept;
        const fdualquat& getTranslationAndRotation(void) const noexcept;
        const vec3& getScale(void) const noexcept;
    private:
        fdualquat translationAndRotation = fdualquat(fquat(1.f, 0.f, 0.f, 0.f), vec3(0.f, 0.f, 0.f));
        vec3 scale = vec3(1.f, 1.f, 1.f);
    };

    Transform inverse(const Transform& transform) noexcept;

    Transform translate(const Transform& transform, const vec3& t) noexcept;
    Transform translate(const Transform& transform, const float& tX, const float& tY, const float& tZ) noexcept;

    Transform rotate(const Transform& transform, const vec3& degrees) noexcept;
    Transform rotate(const Transform& transform, const float& degreesX, const float& degreesY, const float& degreesZ) noexcept;
    Transform generalRotate(const Transform& transform, const float& degrees, const vec3& axis) noexcept;

    Transform orbit(const Transform& transform, const vec3& degrees) noexcept;
    Transform orbit(const Transform& transform, const float& degreesX, const float& degreesY, const float& degreesZ) noexcept;
    Transform generalOrbit(const Transform& transform, const float& degrees, const vec3& axis) noexcept;

    Transform scale(const Transform& transform, const vec3& s) noexcept;
    Transform scale(const Transform& transform, const float& sX, const float& sY, const float& sZ) noexcept;
}

#endif // !PUGGO_TRANSFORM_HPP
