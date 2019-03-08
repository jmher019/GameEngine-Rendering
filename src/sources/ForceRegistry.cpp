#include <ForceRegistry.hpp>

using namespace puggo;

void ForceRegistry::addAnchoredSpringForce(
    const AnchoredSpringForceGenerator& generator,
    const TransformComponentHandle& transformHandle,
    const PhysicsComponentHandle& physicsHandle
) noexcept {
    anchoredSpringForces.push_back({
        generator,
        transformHandle,
        physicsHandle
    });
}

void ForceRegistry::addCenterMassForce(
    const CenterMassForceGenerator& generator,
    const TransformComponentHandle& transformHandle,
    const PhysicsComponentHandle& physicsHandle
) noexcept {
    centerMassForces.push_back({
        generator,
        transformHandle,
        physicsHandle
    });
}

void ForceRegistry::addPositionForce(
    const PositionForceGenerator& generator,
    const TransformComponentHandle& transformHandle,
    const PhysicsComponentHandle& physicsHandle
) noexcept {
    positionForces.push_back({
        generator,
        transformHandle,
        physicsHandle
    });
}

void ForceRegistry::addSpringForce(
    const SpringForceGenerator& generator,
    const TransformComponentHandle& transformHandle,
    const PhysicsComponentHandle& physicsHandle
) noexcept {
    springForces.push_back({
        generator,
        transformHandle,
        physicsHandle
    });
}

void ForceRegistry::removeAllForces(const SceneObject& sceneObject) noexcept {
    for (auto it = anchoredSpringForces.begin(); it != anchoredSpringForces.end();) {
        if ((*it).transformHandle == sceneObject.getTransformCompHandle() && (*it).physicsHandle == sceneObject.getPhysicsCompHandle()) {
            it = anchoredSpringForces.erase(it);
        }
        else {
            ++it;
        }
    }

    for (auto it = centerMassForces.begin(); it != centerMassForces.end();) {
        if ((*it).transformHandle == sceneObject.getTransformCompHandle() && (*it).physicsHandle == sceneObject.getPhysicsCompHandle()) {
            it = centerMassForces.erase(it);
        }
        else {
            ++it;
        }
    }

    for (auto it = positionForces.begin(); it != positionForces.end();) {
        if ((*it).transformHandle == sceneObject.getTransformCompHandle() && (*it).physicsHandle == sceneObject.getPhysicsCompHandle()) {
            it = positionForces.erase(it);
        }
        else {
            ++it;
        }
    }

    for (auto it = springForces.begin(); it != springForces.end();) {
        if ((*it).transformHandle == sceneObject.getTransformCompHandle() && (*it).physicsHandle == sceneObject.getPhysicsCompHandle()) {
            it = springForces.erase(it);
        }
        else {
            ++it;
        }
    }
}

const vector<ForceGenAndObject<AnchoredSpringForceGenerator>>& ForceRegistry::getAnchoredSpringForces(void) const noexcept {
    return anchoredSpringForces;
}

const vector<ForceGenAndObject<CenterMassForceGenerator>>& ForceRegistry::getCenterMassForces(void) const noexcept {
    return centerMassForces;
}

const vector<ForceGenAndObject<PositionForceGenerator>>& ForceRegistry::getPositionForces(void) const noexcept {
    return positionForces;
}

const vector<ForceGenAndObject<SpringForceGenerator>>& ForceRegistry::getSpringForces(void) const noexcept {
    return springForces;
}