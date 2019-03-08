#ifndef PUGGO_PHYSICS_COMPONENT_HPP
#define PUGGO_PHYSICS_COMPONENT_HPP

#include <glm/glm.hpp>

using namespace glm;
using namespace std;

namespace puggo {
    class PhysicsComponent {
    public:
        PhysicsComponent(void) noexcept;
        PhysicsComponent(const PhysicsComponent& physicsComponent) noexcept;
        PhysicsComponent(PhysicsComponent&& physicsComponent) noexcept;

        PhysicsComponent& operator=(const PhysicsComponent& physicsComponent) noexcept;
        PhysicsComponent& operator=(PhysicsComponent&& physicsComponent) noexcept;

        const float& getMass(void) const noexcept;
        void setMass(const float& mass) noexcept;

        const vec3& getVelocity(void) const noexcept;
        void setVelocity(const vec3& velocity) noexcept;

        const vec3& getAccumulatedForces(void) const noexcept;
        void setAccumulatedForces(const vec3& accumulatedForces) noexcept;

    private:
        float mass = 1.f;
        vec3 velocity = vec3(0.f, 0.f, 0.f);
        vec3 accumulatedForces = vec3(0.f, 0.f, 0.f);
    };
}

#endif // !PUGGO_PHYSICS_COMPONENT_HPP
