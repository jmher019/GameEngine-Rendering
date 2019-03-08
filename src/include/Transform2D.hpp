#ifndef PUGGO_TRANSFORM_2D_HPP
#define PUGGO_TRANSFORM_2D_HPP

#include <glm/glm.hpp>

using namespace glm;

namespace puggo {
    struct Transform2D {
        vec2 translation;
        vec2 scales;
        float rotation;

        void translate(const vec2& translation) noexcept;
        void rotate(const float& degrees) noexcept;
        void orbit(const float& degrees, const vec2& origin) noexcept;
        void scale(const vec2& scales) noexcept;
    };

    Transform2D createIdentityTransform2D(void) noexcept;
    Transform2D translate(const Transform2D& transform, const vec2& translation) noexcept;
    Transform2D rotate(const Transform2D& transform, const float& degrees) noexcept;
    Transform2D orbit(const Transform2D& transform, const float& degrees, const vec2& origin) noexcept;
    Transform2D scale(const Transform2D& transform, const vec2& scales) noexcept;

    Transform2D operator*(const Transform2D& left, const Transform2D& right) noexcept;
    bool operator==(const Transform2D& left, const Transform2D& right) noexcept;

    mat4 convertToMatrix(const Transform2D& transform) noexcept;
    mat4 convertToInverseMatrix(const Transform2D& transform) noexcept;
}

#endif // !PUGGO_TRANSFORM_2D_HPP
