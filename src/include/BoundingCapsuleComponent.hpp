#ifndef PUGGO_BOUNDING_CAPSULE_COMPONENT_HPP
#define PUGGO_BOUNDING_CAPSULE_COMPONENT_HPP

#include <glm/gtc/type_ptr.hpp>

#include <Segment.hpp>
#include <Transform.hpp>

namespace puggo {
    class BoundingCapsuleComponent {
    public:
        BoundingCapsuleComponent(const float& radius = 0.f, const float& capsuleCylinderLength = 0.f);
        BoundingCapsuleComponent(const BoundingCapsuleComponent& sphere);
        BoundingCapsuleComponent(BoundingCapsuleComponent&& sphere) noexcept;

        BoundingCapsuleComponent& operator=(const BoundingCapsuleComponent& sphere);
        BoundingCapsuleComponent& operator=(BoundingCapsuleComponent&& sphere) noexcept;
        bool operator==(const BoundingCapsuleComponent& component) noexcept;

        const float& getRadius(void) const noexcept;
        void setRadius(const float& radius) noexcept;
        const float& getCapsuleCylinderLength(void) const noexcept;
        void setCapsuleCylinderLength(const float& radius) noexcept;

        float getActualRadius(const Transform& transform) const noexcept;
        float getActualCapsuleCylinderLength(const Transform& transform) const noexcept;
        Segment getActualSegment(const Transform& transform) const noexcept;
        vec3 getCenter(const Transform& transform) const noexcept;

    private:
        float radius = 0.f;
        float capsuleCylinderLength;
    };
}

#endif // !PUGGO_BOUNDING_CAPSULE_COMPONENT_HPP
