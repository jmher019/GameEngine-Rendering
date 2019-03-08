#include <BoundingBoxComponent.hpp>

using namespace puggo;

BoundingBoxComponent::BoundingBoxComponent(const vec3& halfExtents):
    halfExtents(halfExtents) {
}

BoundingBoxComponent::BoundingBoxComponent(const BoundingBoxComponent& component):
    halfExtents(component.halfExtents) {
}

BoundingBoxComponent::BoundingBoxComponent(BoundingBoxComponent&& component) noexcept:
    halfExtents(move(component.halfExtents)) {
}

BoundingBoxComponent& BoundingBoxComponent::operator=(const BoundingBoxComponent& component) {
    halfExtents = component.halfExtents;

    return *this;
}

BoundingBoxComponent& BoundingBoxComponent::operator=(BoundingBoxComponent&& component) noexcept {
    halfExtents = move(component.halfExtents);

    return *this;
}

bool BoundingBoxComponent::operator==(const BoundingBoxComponent& component) noexcept {
    return halfExtents == component.halfExtents;
}

const vec3& BoundingBoxComponent::getHalfExtents(void) const noexcept {
    return halfExtents;
}

void BoundingBoxComponent::setHalfExtents(const vec3& halfExtents) noexcept {
    this->halfExtents = halfExtents;
}

vec3 BoundingBoxComponent::getActualHalfExtents(const Transform& transform) const noexcept {
    return halfExtents * glm::abs(transform.getScale());
}

vec3 BoundingBoxComponent::getCenter(const Transform& transform) const noexcept {
    return vec3(transform.getMatrix()[3]);
}

vector<Triangle> BoundingBoxComponent::getTriangles(const Transform& transform) const noexcept {
    vector<Triangle> triangles;

    const vec3 halfExtents = getActualHalfExtents(transform);
    const vec3 center = getCenter(transform);
    const vec3 transformedX = halfExtents.x * transform.getXUnitVector();
    const vec3 transformedY = halfExtents.y * transform.getYUnitVector();
    const vec3 transformedZ = halfExtents.z * transform.getZUnitVector();

    // +x transformed face
    triangles.push_back(Triangle(
        center + transformedX - transformedY + transformedZ,
        center + transformedX - transformedY - transformedZ,
        center + transformedX + transformedY + transformedZ
    ));

    triangles.push_back(Triangle(
        center + transformedX - transformedY - transformedZ,
        center + transformedX + transformedY - transformedZ,
        center + transformedX + transformedY + transformedZ
    ));

    // -x transformed face
    triangles.push_back(Triangle(
        center - transformedX - transformedY + transformedZ,
        center - transformedX + transformedY + transformedZ,
        center - transformedX - transformedY - transformedZ
    ));

    triangles.push_back(Triangle(
        center - transformedX - transformedY - transformedZ,
        center - transformedX + transformedY + transformedZ,
        center - transformedX + transformedY - transformedZ
    ));

    // +y transformed face
    triangles.push_back(Triangle(
        center - transformedX + transformedY + transformedZ,
        center + transformedX + transformedY + transformedZ,
        center - transformedX + transformedY - transformedZ
    ));

    triangles.push_back(Triangle(
        center + transformedX + transformedY + transformedZ,
        center + transformedX + transformedY - transformedZ,
        center - transformedX + transformedY - transformedZ
    ));

    // -y transformed face
    triangles.push_back(Triangle(
        center - transformedX - transformedY + transformedZ,
        center - transformedX - transformedY - transformedZ,
        center + transformedX - transformedY + transformedZ
    ));

    triangles.push_back(Triangle(
        center + transformedX - transformedY + transformedZ,
        center - transformedX - transformedY - transformedZ,
        center + transformedX - transformedY - transformedZ
    ));

    // +z transformed face
    triangles.push_back(Triangle(
        center - transformedX - transformedY + transformedZ,
        center + transformedX - transformedY + transformedZ,
        center - transformedX + transformedY + transformedZ
    ));

    triangles.push_back(Triangle(
        center + transformedX - transformedY + transformedZ,
        center + transformedX + transformedY + transformedZ,
        center - transformedX + transformedY + transformedZ
    ));

    // -z transformed face
    triangles.push_back(Triangle(
        center - transformedX - transformedY - transformedZ,
        center - transformedX + transformedY - transformedZ,
        center + transformedX - transformedY - transformedZ
    ));

    triangles.push_back(Triangle(
        center + transformedX - transformedY - transformedZ,
        center - transformedX + transformedY - transformedZ,
        center + transformedX + transformedY - transformedZ
    ));

    return triangles;
}