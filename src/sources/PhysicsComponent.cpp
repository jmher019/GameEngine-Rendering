#include <PhysicsComponent.hpp>

using namespace puggo;

PhysicsComponent::PhysicsComponent(void) noexcept {}

PhysicsComponent::PhysicsComponent(const PhysicsComponent& physicsComponent) noexcept:
    mass(physicsComponent.mass),
    velocity(physicsComponent.velocity),
    accumulatedForces(physicsComponent.accumulatedForces) {
}

PhysicsComponent::PhysicsComponent(PhysicsComponent&& physicsComponent) noexcept:
    mass(move(physicsComponent.mass)),
    velocity(move(physicsComponent.velocity)),
    accumulatedForces(move(physicsComponent.accumulatedForces)) {
}

PhysicsComponent& PhysicsComponent::operator=(const PhysicsComponent& physicsComponent) noexcept {
    mass = physicsComponent.mass;
    velocity = physicsComponent.velocity;
    accumulatedForces = physicsComponent.accumulatedForces;

    return *this;
}

PhysicsComponent& PhysicsComponent::operator=(PhysicsComponent&& physicsComponent) noexcept {
    mass = move(physicsComponent.mass);
    velocity = move(physicsComponent.velocity);
    accumulatedForces = move(physicsComponent.accumulatedForces);

    return *this;
}

const float& PhysicsComponent::getMass(void) const noexcept {
    return mass;
}

void PhysicsComponent::setMass(const float& mass) noexcept {
    this->mass = mass;
}

const vec3& PhysicsComponent::getVelocity(void) const noexcept {
    return velocity;
}

void PhysicsComponent::setVelocity(const vec3& velocity) noexcept {
    this->velocity = velocity;
}

const vec3& PhysicsComponent::getAccumulatedForces(void) const noexcept {
    return this->accumulatedForces;
}

void PhysicsComponent::setAccumulatedForces(const vec3& accumulatedForces) noexcept {
    this->accumulatedForces = accumulatedForces;
}