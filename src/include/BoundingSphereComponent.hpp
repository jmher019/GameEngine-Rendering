#ifndef PUGGO_BOUNDING_SPHERE_COMPONENT_HPP
#define PUGGO_BOUNDING_SPHERE_COMPONENT_HPP

#include <Transform.hpp>

using namespace std;

namespace puggo {
    class BoundingSphereComponent {
    public:
        BoundingSphereComponent(const float& radius);
        BoundingSphereComponent(const BoundingSphereComponent& sphere);
        BoundingSphereComponent(BoundingSphereComponent&& sphere) noexcept;

        BoundingSphereComponent& operator=(const BoundingSphereComponent& sphere);
        BoundingSphereComponent& operator=(BoundingSphereComponent&& sphere) noexcept;
        bool operator==(const BoundingSphereComponent& component) noexcept;

        const float& getRadius(void) const noexcept;
        void setRadius(const float& radius) noexcept;
        float getActualRadius(const Transform& transform) const noexcept;
        vec3 getCenter(const Transform& transform) const noexcept;

    private:
        float radius = 0.f;
    };
}

#endif // !PUGGO_BOUNDING_SPHERE_COMPONENT_HPP
