#include <Plane.hpp>

using namespace puggo;

Plane::Plane(const vec3& normal, const float& planeScalar) noexcept:
    normal(normal),
    planeScalar(planeScalar) {
}

Plane::Plane(const Plane& plane) noexcept:
    normal(plane.normal),
    planeScalar(plane.planeScalar) {
}

Plane::Plane(Plane&& plane) noexcept :
    normal(move(plane.normal)),
    planeScalar(move(plane.planeScalar)) {
}

Plane& Plane::operator=(const Plane& plane) noexcept {
    normal = plane.normal;
    planeScalar = plane.planeScalar;

    return *this;
}

Plane& Plane::operator=(Plane&& plane) noexcept {
    normal = move(plane.normal);
    planeScalar = move(plane.planeScalar);

    return *this;
}

const vec3& Plane::getNormal(void) const noexcept {
    return normal;
}

void Plane::setNormal(const vec3& normal) noexcept {
    this->normal = normal;
}

const float& Plane::getPlaneScalar(void) const noexcept {
    return planeScalar;
}

void Plane::setPlaneScalar(const float& planeScalar) noexcept {
    this->planeScalar = planeScalar;
}

vec3 Plane::computeClosestPointOnPlane(const vec3& target) const noexcept {
    const float t = (dot(normal, target) - planeScalar) / dot(normal, normal);
    return target - t * normal;
}

bool Plane::isPointOutsideOfPlane(const vec3& target) const noexcept {
    return fabs(dot(target, normal) - planeScalar) > GeometryConstants::EPSILON;
}

bool Plane::arePointsOnOppositeSides(const vec3& target1, const vec3& target2) const noexcept {
    const float signp1 = dot(vec4(target1, 1.f), vec4(normal, planeScalar));
    const float signp2 = dot(vec4(target2, 1.f), vec4(normal, planeScalar));

    return signp1 * signp2 < 0.f;
}