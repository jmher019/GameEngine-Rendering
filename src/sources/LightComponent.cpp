#include <LightComponent.hpp>

using namespace puggo;

LightComponent::LightComponent(void) noexcept {}

LightComponent::LightComponent(const LightComponent& lightComponent) noexcept:
    ambient(lightComponent.ambient),
    diffuse(lightComponent.diffuse),
    specular(lightComponent.specular) {
}

LightComponent::LightComponent(LightComponent&& lightComponent) noexcept:
    ambient(move(lightComponent.ambient)),
    diffuse(move(lightComponent.diffuse)),
    specular(move(lightComponent.specular)) {
}

LightComponent& LightComponent::operator=(const LightComponent& lightComponent) noexcept {
    ambient = lightComponent.ambient;
    diffuse = lightComponent.diffuse;
    specular = lightComponent.specular;

    return *this;
}

LightComponent& LightComponent::operator=(LightComponent&& lightComponent) noexcept {
    ambient = move(lightComponent.ambient);
    diffuse = move(lightComponent.diffuse);
    specular = move(lightComponent.specular);

    return *this;
}

const vec3& LightComponent::getAmbient(void) const noexcept {
    return ambient;
}

void LightComponent::setAmbient(const vec3& ambient) noexcept {
    this->ambient = ambient;
}

const vec3& LightComponent::getDiffuse(void) const noexcept {
    return diffuse;
}

void LightComponent::setDiffuse(const vec3& diffuse) noexcept {
    this->diffuse = diffuse;
}

const vec3& LightComponent::getSpecular(void) const noexcept {
    return specular;
}

void LightComponent::setSpecular(const vec3& specular) noexcept {
    this->specular = specular;
}