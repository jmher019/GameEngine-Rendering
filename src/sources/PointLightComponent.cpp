#include <PointLightComponent.hpp>

using namespace puggo;

PointLightComponent::PointLightComponent(void) noexcept:
    LightComponent() {
}

PointLightComponent::PointLightComponent(const PointLightComponent& pointLightComponent) noexcept:
    LightComponent(pointLightComponent),
    constant(pointLightComponent.constant),
    linear(pointLightComponent.linear),
    quadratic(pointLightComponent.quadratic) {
}

PointLightComponent::PointLightComponent(PointLightComponent&& pointLightComponent) noexcept:
    LightComponent(forward<LightComponent>(pointLightComponent)),
    constant(move(pointLightComponent.constant)),
    linear(move(pointLightComponent.linear)),
    quadratic(move(pointLightComponent.quadratic)) {
}

PointLightComponent& PointLightComponent::operator=(const PointLightComponent& pointLightComponent) noexcept {
    LightComponent::operator=(pointLightComponent);
    constant = pointLightComponent.constant;
    linear = pointLightComponent.linear;
    quadratic = pointLightComponent.quadratic;

    return *this;
}

PointLightComponent& PointLightComponent::operator=(PointLightComponent&& pointLightComponent) noexcept {
    LightComponent::operator=(forward<LightComponent>(pointLightComponent));
    constant = move(pointLightComponent.constant);
    linear = move(pointLightComponent.linear);
    quadratic = move(pointLightComponent.quadratic);

    return *this;
}

const float& PointLightComponent::getConstant(void) const noexcept {
    return constant;
}

void PointLightComponent::setConstant(const float& constant) noexcept {
    this->constant = constant;
}

const float& PointLightComponent::getLinear(void) const noexcept {
    return linear;
}

void PointLightComponent::setLinear(const float& linear) noexcept {
    this->linear = linear;
}

const float& PointLightComponent::getQuadratic(void) const noexcept {
    return quadratic;
}

void PointLightComponent::setQuadratic(const float& quadratic) noexcept {
    this->quadratic = quadratic;
}