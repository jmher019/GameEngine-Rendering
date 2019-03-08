#include <DirectionalLightComponent.hpp>

using namespace puggo;

DirectionalLightComponent::DirectionalLightComponent(void) noexcept:
    LightComponent() {
}

DirectionalLightComponent::DirectionalLightComponent(const DirectionalLightComponent& directionalLightComponent) noexcept:
    LightComponent(directionalLightComponent),
    direction(directionalLightComponent.direction) {
}

DirectionalLightComponent::DirectionalLightComponent(DirectionalLightComponent&& directionalLightComponent) noexcept:
    LightComponent(forward<LightComponent>(directionalLightComponent)),
    direction(move(directionalLightComponent.direction)) {
}

DirectionalLightComponent& DirectionalLightComponent::operator=(const DirectionalLightComponent& directionalLightComponent) noexcept {
    LightComponent::operator=(directionalLightComponent);
    direction = directionalLightComponent.direction;

    return *this;
}

DirectionalLightComponent& DirectionalLightComponent::operator=(DirectionalLightComponent&& directionalLightComponent) noexcept {
    LightComponent::operator=(forward<LightComponent>(directionalLightComponent));
    direction = move(directionalLightComponent.direction);

    return *this;
}

const vec3& DirectionalLightComponent::getDirection(void) const noexcept {
    return direction;
}

void DirectionalLightComponent::setDirection(const vec3& direction) noexcept {
    this->direction = direction;
}