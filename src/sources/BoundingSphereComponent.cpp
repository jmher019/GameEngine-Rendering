#include <BoundingSphereComponent.hpp>

using namespace puggo;

BoundingSphereComponent::BoundingSphereComponent(const float& radius):
    radius(radius) {
}

BoundingSphereComponent::BoundingSphereComponent(const BoundingSphereComponent& component) :
    radius(component.radius) {
}

BoundingSphereComponent::BoundingSphereComponent(BoundingSphereComponent&& component) noexcept:
    radius(move(component.radius)) {
}

BoundingSphereComponent& BoundingSphereComponent::operator=(const BoundingSphereComponent& component) {
    radius = component.radius;
    
    return *this;
}

BoundingSphereComponent& BoundingSphereComponent::operator=(BoundingSphereComponent&& component) noexcept {
    radius = move(component.radius);

    return *this;
}

bool BoundingSphereComponent::operator==(const BoundingSphereComponent& component) noexcept {
    return radius == component.radius;
}

const float& BoundingSphereComponent::getRadius(void) const noexcept {
    return radius;
}

void BoundingSphereComponent::setRadius(const float& radius) noexcept {
    this->radius = radius;
}

float BoundingSphereComponent::getActualRadius(const Transform& transform) const noexcept {
    const vec3 scaledRadii = glm::abs(transform.getScale()) * radius;
    return glm::max(glm::max(scaledRadii.x, scaledRadii.y), scaledRadii.z);
}

vec3 BoundingSphereComponent::getCenter(const Transform& transform) const noexcept {
    return vec3(transform.getMatrix()[3]);
}