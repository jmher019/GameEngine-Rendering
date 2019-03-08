#include <TransformComponent.hpp>

using namespace puggo;

TransformComponent::TransformComponent(void):
    localTransform(Transform()),
    globalTransform(Transform()) {
}

TransformComponent::TransformComponent(const TransformComponent& component):
    localTransform(component.localTransform),
    globalTransform(component.globalTransform) {
}

TransformComponent::TransformComponent(TransformComponent&& component) noexcept:
    localTransform(move(component.localTransform)),
    globalTransform(move(component.globalTransform)) {
}

TransformComponent& TransformComponent::operator=(const TransformComponent& component) {
    localTransform = component.localTransform;
    globalTransform = component.globalTransform;

    return *this;
}

TransformComponent& TransformComponent::operator=(TransformComponent&& component) noexcept {
    localTransform = move(component.localTransform);
    globalTransform = move(component.globalTransform);

    return *this;
}

bool TransformComponent::operator==(const TransformComponent& component) noexcept {
    return localTransform == component.localTransform && globalTransform == component.globalTransform;
}

const Transform& TransformComponent::getLocalTransform(void) const {
    return localTransform;
}

const Transform& TransformComponent::getGlobalTransform(void) const {
    return globalTransform;
}

void TransformComponent::translate(const vec3& t) {
    translate(t.x, t.y, t.z);
}

void TransformComponent::translate(const float& tX, const float& tY, const float& tZ) {
    localTransform = puggo::translate(localTransform, tX, tY, tZ);
}

void TransformComponent::rotate(const vec3& degrees) {
    rotate(degrees.x, degrees.y, degrees.z);
}

void TransformComponent::rotate(const float& degreesX, const float& degreesY, const float& degreesZ) {
    localTransform = puggo::rotate(localTransform, degreesX, degreesY, degreesZ);
}

void TransformComponent::generalRotate(const float& degrees, const vec3& axis) {
    localTransform = puggo::generalRotate(localTransform, degrees, axis);
}

void TransformComponent::orbit(const vec3& degrees) {
    orbit(degrees.x, degrees.y, degrees.z);
}

void TransformComponent::orbit(const float& degreesX, const float& degreesY, const float& degreesZ) {
    localTransform = puggo::orbit(localTransform, degreesX, degreesY, degreesZ);
}

void TransformComponent::generalOrbit(const float& degrees, const vec3& axis) {
    localTransform = puggo::generalOrbit(localTransform, degrees, axis);
}

void TransformComponent::scale(const vec3& s) {
    scale(s.x, s.y, s.z);
}

void TransformComponent::scale(const float& sX, const float& sY, const float& sZ) {
    localTransform = puggo::scale(localTransform, sX, sY, sZ);
}

void TransformComponent::updateGlobalTransform(const Transform& parentTransform) {
    globalTransform = parentTransform * localTransform;
}