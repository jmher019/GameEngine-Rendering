#ifndef PUGGO_BOUNDING_BOX_COMPONENT
#define PUGGO_BOUNDING_BOX_COMPONENT

#include <vector>

#include <Triangle.hpp>
#include <Transform.hpp>

using namespace std;

namespace puggo {
    class BoundingBoxComponent {
    public:
        BoundingBoxComponent(const vec3& halfExtents);
        BoundingBoxComponent(const BoundingBoxComponent& component);
        BoundingBoxComponent(BoundingBoxComponent&& component) noexcept;

        BoundingBoxComponent& operator=(const BoundingBoxComponent& component);
        BoundingBoxComponent& operator=(BoundingBoxComponent&& component) noexcept;
        bool operator==(const BoundingBoxComponent& component) noexcept;

        const vec3& getHalfExtents(void) const noexcept;
        void setHalfExtents(const vec3& halfExtents) noexcept;

        vec3 getActualHalfExtents(const Transform& transform) const noexcept;
        vec3 getCenter(const Transform& transform) const noexcept;
        vector<Triangle> getTriangles(const Transform& transform) const noexcept;

    private:
        vec3 halfExtents;
    };
}

#endif // !PUGGO_BOUNDING_BOX_COMPONENT
