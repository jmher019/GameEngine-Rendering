#include <Transform2D.hpp>

using namespace puggo;

void Transform2D::translate(const vec2& translation) noexcept {
    this->translation += translation;
}

void Transform2D::rotate(const float& degrees) noexcept {
    this->rotation += degrees;
}

void Transform2D::orbit(const float& degrees, const vec2& origin) noexcept {
    const vec2 offset = this->translation - origin;
    const float COS = cos(radians(degrees));
    const float SIN = sin(radians(degrees));

    this->translation = origin + vec2(COS * offset.x - SIN * offset.y, SIN * offset.x + COS * offset.y);
    this->rotation += degrees;
}

void Transform2D::scale(const vec2& scales) noexcept {
    this->scales = this->scales * scales;
}

Transform2D puggo::createIdentityTransform2D(void) noexcept {
    return {
        vec2(0.f, 0.f),
        vec2(1.f, 1.f),
        0.f
    };
}

Transform2D puggo::translate(const Transform2D& transform, const vec2& translation) noexcept {
    return {
        transform.translation + translation,
        transform.scales,
        transform.rotation
    };
}

Transform2D puggo::rotate(const Transform2D& transform, const float& degrees) noexcept {
    return {
        transform.translation,
        transform.scales,
        transform.rotation + degrees
    };
}

Transform2D puggo::orbit(const Transform2D& transform, const float& degrees, const vec2& origin) noexcept {
    const vec2 offset = transform.translation - origin;
    const float COS = cos(radians(degrees));
    const float SIN = sin(radians(degrees));

    return {
        origin + vec2(COS * offset.x - SIN * offset.y, SIN * offset.x + COS * offset.y),
        transform.scales,
        transform.rotation + degrees
    };
}

Transform2D puggo::scale(const Transform2D& transform, const vec2& scales) noexcept {
    return {
        transform.translation,
        transform.scales * scales,
        transform.rotation
    };
}

Transform2D puggo::operator*(const Transform2D& left, const Transform2D& right) noexcept {
    return {
        left.translation + right.translation,
        left.scales * right.scales,
        left.rotation + right.rotation
    };
}

bool puggo::operator==(const Transform2D& left, const Transform2D& right) noexcept {
    return left.translation == right.translation && left.scales == right.scales && left.rotation == right.rotation;
}

mat4 puggo::convertToMatrix(const Transform2D& transform) noexcept {
    mat4 mat(1.f);
    const float COS = cos(radians(transform.rotation));
    const float SIN = sin(radians(transform.rotation));

    mat[0][0] = transform.scales.x * COS;
    mat[1][0] = -SIN;
    mat[3][0] = transform.translation.x;
    mat[0][1] = SIN;
    mat[1][1] = transform.scales.y * COS;
    mat[3][1] = transform.translation.y;

    return mat;
}

mat4 puggo::convertToInverseMatrix(const Transform2D& transform) noexcept {
    mat4 mat(1.f);
    const float COS = cos(radians(-transform.rotation));
    const float SIN = sin(radians(-transform.rotation));
    const float scaleX = 1.f / transform.scales.x;
    const float scaleY = 1.f / transform.scales.y;

    mat[0][0] = scaleX * COS;
    mat[1][0] = -SIN;
    mat[3][0] = scaleX * (transform.translation.x * COS - transform.translation.y * SIN);
    mat[0][1] = SIN;
    mat[1][1] = scaleY * COS;
    mat[3][1] = scaleY * (transform.translation.x * SIN + transform.translation.y * COS);

    return mat;
}