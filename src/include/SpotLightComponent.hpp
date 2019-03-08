#ifndef PUGGO_SPOT_LIGHT_COMPONENT_HPP
#define PUGGO_SPOT_LIGHT_COMPONENT_HPP

#include <LightComponent.hpp>

namespace puggo {
    class SpotLightComponent : public LightComponent {
    public:
        SpotLightComponent(void) noexcept;
        SpotLightComponent(const SpotLightComponent& spotLightComponent) noexcept;
        SpotLightComponent(SpotLightComponent&& spotLightComponent) noexcept;

        SpotLightComponent& operator=(const SpotLightComponent& spotLightComponent) noexcept;
        SpotLightComponent& operator=(SpotLightComponent&& spotLightComponent) noexcept;

        const vec3& getDirection(void) const noexcept;
        void setDirection(const vec3& direction) noexcept;

        const float& getCutOff(void) const noexcept;
        void setCutOff(const float& cutOff) noexcept;

    private:
        vec3 direction;
        float cutOff;
    };
}

#endif // !PUGGO_SPOT_LIGHT_COMPONENT_HPP
