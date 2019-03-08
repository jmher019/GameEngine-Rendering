#ifndef PUGGO_TRIANGLE_HPP
#define PUGGO_TRIANGLE_HPP

#include <glm/glm.hpp>

#include <GeometryConstants.hpp>

using namespace glm;
using namespace std;

namespace puggo {
    class Triangle {
    public:
        Triangle(const vec3& vertex1, const vec3& vertex2, const vec3& vertex3) noexcept;
        Triangle(const Triangle& triangle) noexcept;
        Triangle(Triangle&& triangle) noexcept;

        Triangle& operator=(const Triangle& triangle) noexcept;
        Triangle& operator=(Triangle&& triangle) noexcept;

        const vec3& getVertex1(void) const noexcept;
        void setVertex1(const vec3& vertex1) noexcept;
        const vec3& getVertex2(void) const noexcept;
        void setVertex2(const vec3& vertex2) noexcept;
        const vec3& getVertex3(void) const noexcept;
        void setVertex3(const vec3& vertex3) noexcept;

        vec3 computeNormal(void) const noexcept;
        vec3 computeBarycentricCoord(const vec3& target) const noexcept;
        vec3 computeCenter(void) const noexcept;
        bool isWithinTriangle(const vec3& target) const noexcept;
        vec3 computeClosestPointOnTriangle(const vec3& target) const noexcept;

    private:
        vec3 vertex1;
        vec3 vertex2;
        vec3 vertex3;
    };
}

#endif // !PUGGO_TRIANGLE_HPP
