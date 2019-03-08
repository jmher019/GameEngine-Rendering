#ifndef PUGGO_DIRECTIONAL_LIGHT_COMPONENT_HPP
#define PUGGO_DIRECTIONAL_LIGHT_COMPONENT_HPP

#include <LightComponent.hpp>

namespace puggo {
    class DirectionalLightComponent : public LightComponent {
    public:
        DirectionalLightComponent(void) noexcept;
        DirectionalLightComponent(const DirectionalLightComponent& directionalLightComponent) noexcept;
        DirectionalLightComponent(DirectionalLightComponent&& directionalLightComponent) noexcept;

        DirectionalLightComponent& operator=(const DirectionalLightComponent& directionalLightComponent) noexcept;
        DirectionalLightComponent& operator=(DirectionalLightComponent&& directionalLightComponent) noexcept;

        const vec3& getDirection(void) const noexcept;
        void setDirection(const vec3& direction) noexcept;

    private:
        vec3 direction;
    };
}

#endif // !PUGGO_DIRECTIONAL_LIGHT_COMPONENT_HPP
