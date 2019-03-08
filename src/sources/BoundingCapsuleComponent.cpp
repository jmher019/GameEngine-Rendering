#include <BoundingCapsuleComponent.hpp>

using namespace puggo;

BoundingCapsuleComponent::BoundingCapsuleComponent(
    const float& radius,
    const float& capsuleCylinderLength
):
    radius(radius),
    capsuleCylinderLength(capsuleCylinderLength) {
}

BoundingCapsuleComponent::BoundingCapsuleComponent(const BoundingCapsuleComponent& component):
    radius(component.radius),
    capsuleCylinderLength(component.capsuleCylinderLength) {
}

BoundingCapsuleComponent::BoundingCapsuleComponent(BoundingCapsuleComponent&& component) noexcept:
    radius(move(component.radius)),
    capsuleCylinderLength(move(component.capsuleCylinderLength)) {
}

BoundingCapsuleComponent& BoundingCapsuleComponent::operator=(const BoundingCapsuleComponent& component) {
    radius = component.radius;
    capsuleCylinderLength = component.capsuleCylinderLength;

    return *this;
}

BoundingCapsuleComponent& BoundingCapsuleComponent::operator=(BoundingCapsuleComponent&& component) noexcept {
    radius = move(component.radius);
    capsuleCylinderLength = move(component.capsuleCylinderLength);

    return *this;
}

bool BoundingCapsuleComponent::operator==(const BoundingCapsuleComponent& component) noexcept {
    return radius == component.radius && capsuleCylinderLength == component.capsuleCylinderLength;
}

const float& BoundingCapsuleComponent::getRadius(void) const noexcept {
    return radius;
}

void BoundingCapsuleComponent::setRadius(const float& radius) noexcept {
    this->radius = radius;
}

float BoundingCapsuleComponent::getActualRadius(const Transform& transform) const noexcept {
    const vec3 scaledRadii = glm::abs(transform.getScale()) * radius;
    return glm::max(glm::max(scaledRadii.x, scaledRadii.y), scaledRadii.z);
}

const float& BoundingCapsuleComponent::getCapsuleCylinderLength(void) const noexcept {
    return capsuleCylinderLength;
}

void BoundingCapsuleComponent::setCapsuleCylinderLength(const float& capsuleCylinderLength) noexcept {
    this->capsuleCylinderLength = capsuleCylinderLength;
}

float BoundingCapsuleComponent::getActualCapsuleCylinderLength(const Transform& transform) const noexcept {
    return capsuleCylinderLength * glm::abs(transform.getScale().y);
}

Segment BoundingCapsuleComponent::getActualSegment(const Transform& transform) const noexcept {
    const mat4 matrix = (Transform(transform.getTranslationAndRotation())).getMatrix();
    const float halfCapsuleLength = getActualCapsuleCylinderLength(transform) * 0.5f;
    const vec3 topPoint = vec3(matrix * vec4(0.f, halfCapsuleLength, 0.f, 1.f));
    const vec3 bottomPoint = vec3(matrix * vec4(0.f, -halfCapsuleLength, 0.f, 1.f));

    return Segment(bottomPoint, topPoint);
}

vec3 BoundingCapsuleComponent::getCenter(const Transform& transform) const noexcept {
    return vec3(transform.getMatrix()[3]);
}