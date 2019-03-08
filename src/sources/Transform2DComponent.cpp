#include <Transform2DComponent.hpp>

using namespace puggo;

void Transform2DComponent::updateGlobalTransform(const Transform2D& parentTransform) noexcept {
    this->globalTransform = parentTransform * this->localTransform;
}

bool puggo::operator==(const Transform2DComponent& left, const Transform2DComponent& right) noexcept {
    return left.localTransform == right.localTransform && left.globalTransform == right.globalTransform;
}