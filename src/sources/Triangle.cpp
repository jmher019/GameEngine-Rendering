#include <Triangle.hpp>

using namespace puggo;

Triangle::Triangle(const vec3& vertex1, const vec3& vertex2, const vec3& vertex3) noexcept:
    vertex1(vertex1),
    vertex2(vertex2),
    vertex3(vertex3) {
}

Triangle::Triangle(const Triangle& triangle) noexcept:
    vertex1(triangle.vertex1),
    vertex2(triangle.vertex2),
    vertex3(triangle.vertex3) {
}

Triangle::Triangle(Triangle&& triangle) noexcept:
    vertex1(move(triangle.vertex1)),
    vertex2(move(triangle.vertex2)),
    vertex3(move(triangle.vertex3)) {
}

Triangle& Triangle::operator=(const Triangle& triangle) noexcept {
    vertex1 = triangle.vertex1;
    vertex2 = triangle.vertex2;
    vertex3 = triangle.vertex3;

    return *this;
}

Triangle& Triangle::operator=(Triangle&& triangle) noexcept {
    vertex1 = move(triangle.vertex1);
    vertex2 = move(triangle.vertex2);
    vertex3 = move(triangle.vertex3);

    return *this;
}

const vec3& Triangle::getVertex1(void) const noexcept {
    return vertex1;
}

void Triangle::setVertex1(const vec3& vertex1) noexcept {
    this->vertex1 = vertex1;
}

const vec3& Triangle::getVertex2(void) const noexcept {
    return vertex2;
}

void Triangle::setVertex2(const vec3& vertex2) noexcept {
    this->vertex2 = vertex2;
}

const vec3& Triangle::getVertex3(void) const noexcept {
    return vertex3;
}

void Triangle::setVertex3(const vec3& vertex3) noexcept {
    this->vertex3 = vertex3;
}

vec3 Triangle::computeNormal(void) const noexcept {
    return cross(vertex2 - vertex1, vertex3 - vertex2);
}

vec3 Triangle::computeBarycentricCoord(const vec3& target) const noexcept {
    const vec3 vec0 = vertex2 - vertex1;
    const vec3 vec1 = vertex3 - vertex1;
    const vec3 vec2 = target - vertex1;
    const float d00 = dot(vec0, vec0);
    const float d01 = dot(vec0, vec1);
    const float d11 = dot(vec1, vec1);
    const float d20 = dot(vec2, vec0);
    const float d21 = dot(vec2, vec1);
    const float denom = d00 * d11 - d01 * d01;

    const float v = (d11 * d20 - d01 * d21) / denom;
    const float w = (d00 * d21 - d01 * d20) / denom;
    return vec3(1.0f - v - w, v, w);
}

vec3 Triangle::computeCenter(void) const noexcept {
    return (vertex1 + vertex2 + vertex3) / 3.f;
}

bool Triangle::isWithinTriangle(const vec3& target) const noexcept {
    const vec3 barycentricCoord = computeBarycentricCoord(target);

    return barycentricCoord[1] >= 0.0f &&
        barycentricCoord[2] >= 0.0f &&
        (barycentricCoord[1] + barycentricCoord[2]) <= 1.0f;
}

vec3 Triangle::computeClosestPointOnTriangle(const vec3& target) const noexcept {
    // Check if P in vertex region outside A
    const vec3 ab = vertex2 - vertex1;
    const vec3 ac = vertex3 - vertex1;
    const vec3 ap = target - vertex1;
    const float d1 = dot(ab, ap);
    const float d2 = dot(ac, ap);
    if (d1 <= 0.0f && d2 <= 0.0f) {
        return vertex1; // barycentric coordinates (1,0,0)
    }

    // Check if P in vertex region outside B
    const vec3 bp = target - vertex2;
    const float d3 = dot(ab, bp);
    const float d4 = dot(ac, bp);
    if (d3 >= 0.0f && d4 <= d3) {
        return vertex2; // barycentric coordinates (0,1,0)
    }

    // Check if P in edge region of AB, if so return projection of P onto AB
    const float vc = d1 * d4 - d3 * d2;
    if (vc <= 0.0f && d1 >= 0.0f && d3 <= 0.0f) {
        const float v = d1 / (d1 - d3);
        return vertex1 + v * ab; // barycentric coordinates (1-v,v,0)
    }
    // Check if P in vertex region outside C
    const vec3 cp = target - vertex3;
    const float d5 = dot(ab, cp);
    const float d6 = dot(ac, cp);
    if (d6 >= 0.0f && d5 <= d6) {
        return vertex3; // barycentric coordinates (0,0,1)
    }

    // Check if P in edge region of AC, if so return projection of P onto AC
    const float vb = d5 * d2 - d1 * d6;
    if (vb <= 0.0f && d2 >= 0.0f && d6 <= 0.0f) {
        const float w = d2 / (d2 - d6);
        return vertex1 + w * ac; // barycentric coordinates (1-w,0,w)
    }
    // Check if P in edge region of BC, if so return projection of P onto BC
    const float va = d3 * d6 - d5 * d4;
    if (va <= 0.0f && (d4 - d3) >= 0.0f && (d5 - d6) >= 0.0f) {
        const float w = (d4 - d3) / ((d4 - d3) + (d5 - d6));
        return vertex2 + w * (vertex3 - vertex2); // barycentric coordinates (0,1-w,w)
    }
    // P inside face region. Compute Q through its barycentric coordinates (u,v,w)
    const float denom = 1.0f / (va + vb + vc);
    const float v = vb * denom;
    const float w = vc * denom;
    return vertex1 + ab * v + ac * w; // = u*v1 + v*b + w*c, u = va * denom = 1.0f-v-w
}