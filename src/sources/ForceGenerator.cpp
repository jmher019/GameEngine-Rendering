#include <ForceGenerator.hpp>

using namespace puggo;

void puggo::updateForce(const CenterMassForceGenerator& generator, const SceneObject& sceneObject) {
    PhysicsComponent& physicsComp = PhysicsComponentAllocator::get(sceneObject.getPhysicsCompHandle());
    physicsComp.setAccumulatedForces(physicsComp.getAccumulatedForces() + generator.force);
}

void puggo::updateForce(const PositionForceGenerator& generator, const SceneObject& sceneObject) {
    TransformComponent& transformComp = TransformComponentAllocator::get(sceneObject.getTransformCompHandle());
    const vec3 offset = generator.position - vec3(transformComp.getGlobalTransform().getMatrix()[3]);

    if (dot(offset, offset) - generator.range < GeometryConstants::EPSILON) {
        PhysicsComponent& physicsComp = PhysicsComponentAllocator::get(sceneObject.getPhysicsCompHandle());
        physicsComp.setAccumulatedForces(
            physicsComp.getAccumulatedForces() + generator.force * (generator.range - length(offset)) / generator.range
        );
    }
}

void puggo::updateForce(const SpringForceGenerator& generator, const SceneObject& sceneObject) {
    TransformComponent& transformComp = TransformComponentAllocator::get(sceneObject.getTransformCompHandle());
    const vec3 offset = vec3(transformComp.getGlobalTransform().getMatrix()[3]) - generator.position;

    PhysicsComponent& physicsComp = PhysicsComponentAllocator::get(sceneObject.getPhysicsCompHandle());
    physicsComp.setAccumulatedForces(
        physicsComp.getAccumulatedForces() - offset * generator.springConstant
    );
}

void puggo::updateForce(const AnchoredSpringForceGenerator& generator, const SceneObject& sceneObject) {
    TransformComponent& transformComp = TransformComponentAllocator::get(sceneObject.getTransformCompHandle());
    const vec3 offset = vec3(transformComp.getGlobalTransform().getMatrix()[3]) - generator.anchor;
    const float distanceFromRestLength = length(offset) - generator.restLength;

    PhysicsComponent& physicsComp = PhysicsComponentAllocator::get(sceneObject.getPhysicsCompHandle());
    physicsComp.setAccumulatedForces(
        physicsComp.getAccumulatedForces() - normalize(offset) * distanceFromRestLength * generator.springConstant
    );
}