#ifndef PUGGO_FORCE_REGISTRY_HPP
#define PUGGO_FORCE_REGISTRY_HPP

#include <ForceGenerator.hpp>

namespace puggo {
    template <typename T>
    struct ForceGenAndObject {
        T generator;
        TransformComponentHandle transformHandle;
        PhysicsComponentHandle physicsHandle;

        ForceGenAndObject<T>& operator=(const ForceGenAndObject<T>& object) {
            generator = object.generator;
            transformHandle = object.transformHandle;
            physicsHandle = object.physicsHandle;

            return *this;
        }
    };

    class ForceRegistry {
    public:
        void addAnchoredSpringForce(
            const AnchoredSpringForceGenerator& generator,
            const TransformComponentHandle& transformHandle,
            const PhysicsComponentHandle& physicsHandle
        ) noexcept;
        void addCenterMassForce(
            const CenterMassForceGenerator& generator,
            const TransformComponentHandle& transformHandle,
            const PhysicsComponentHandle& physicsHandle
        ) noexcept;
        void addPositionForce(
            const PositionForceGenerator& generator,
            const TransformComponentHandle& transformHandle,
            const PhysicsComponentHandle& physicsHandle
        ) noexcept;
        void addSpringForce(
            const SpringForceGenerator& generator,
            const TransformComponentHandle& transformHandle,
            const PhysicsComponentHandle& physicsHandle
        ) noexcept;

        void removeAllForces(const SceneObject& sceneObject) noexcept;

        const vector<ForceGenAndObject<AnchoredSpringForceGenerator>>& getAnchoredSpringForces(void) const noexcept;
        const vector<ForceGenAndObject<CenterMassForceGenerator>>& getCenterMassForces(void) const noexcept;
        const vector<ForceGenAndObject<PositionForceGenerator>>& getPositionForces(void) const noexcept;
        const vector<ForceGenAndObject<SpringForceGenerator>>& getSpringForces(void) const noexcept;

    private:
        vector<ForceGenAndObject<AnchoredSpringForceGenerator>> anchoredSpringForces;
        vector<ForceGenAndObject<CenterMassForceGenerator>> centerMassForces;
        vector<ForceGenAndObject<PositionForceGenerator>> positionForces;
        vector<ForceGenAndObject<SpringForceGenerator>> springForces;
    };
}

#endif // !PUGGO_FORCE_REGISTRY_HPP
