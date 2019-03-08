#include <SpotLightComponent.hpp>

using namespace puggo;

SpotLightComponent::SpotLightComponent(void) noexcept:
    LightComponent() {
}

SpotLightComponent::SpotLightComponent(const SpotLightComponent& spotLightComponent) noexcept:
    LightComponent(spotLightComponent),
    direction(spotLightComponent.direction),
    cutOff(spotLightComponent.cutOff) {
}

SpotLightComponent::SpotLightComponent(SpotLightComponent&& spotLightComponent) noexcept:
    LightComponent(forward<LightComponent>(spotLightComponent)),
    direction(move(spotLightComponent.direction)),
    cutOff(move(spotLightComponent.cutOff)) {
}

SpotLightComponent& SpotLightComponent::operator=(const SpotLightComponent& spotLightComponent) noexcept {
    LightComponent::operator=(spotLightComponent);
    direction = spotLightComponent.direction;
    cutOff = spotLightComponent.cutOff;

    return *this;
}

SpotLightComponent& SpotLightComponent::operator=(SpotLightComponent&& spotLightComponent) noexcept {
    LightComponent::operator=(forward<LightComponent>(spotLightComponent));
    direction = move(spotLightComponent.direction);
    cutOff = move(spotLightComponent.cutOff);

    return *this;
}

const vec3& SpotLightComponent::getDirection(void) const noexcept {
    return direction;
}

void SpotLightComponent::setDirection(const vec3& direction) noexcept {
    this->direction = direction;
}

const float& SpotLightComponent::getCutOff(void) const noexcept {
    return cutOff;
}

void SpotLightComponent::setCutOff(const float& cutOff) noexcept {
    this->cutOff = cutOff;
}