#ifndef PUGGO_PLANE_HPP
#define PUGGO_PLANE_HPP

#include <glm/glm.hpp>

#include <GeometryConstants.hpp>

using namespace glm;
using namespace std;

namespace puggo {
    class Plane {
    public:
        Plane(const vec3& normal, const float& planeScalar) noexcept;
        Plane(const Plane& plane) noexcept;
        Plane(Plane&& plane) noexcept;
        Plane& operator=(const Plane& plane) noexcept;
        Plane& operator=(Plane&& plane) noexcept;

        const vec3& getNormal(void) const noexcept;
        void setNormal(const vec3& normal) noexcept;
        const float& getPlaneScalar(void) const noexcept;
        void setPlaneScalar(const float& planeScalar) noexcept;

        vec3 computeClosestPointOnPlane(const vec3& target) const noexcept;
        bool isPointOutsideOfPlane(const vec3& target) const noexcept;
        bool arePointsOnOppositeSides(const vec3& target1, const vec3& target2) const noexcept;

    private:
        vec3 normal;
        float planeScalar;
    };
}

#endif // !PUGGO_PLANE_HPP
