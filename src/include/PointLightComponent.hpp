#ifndef PUGGO_POINT_LIGHT_COMPONENT_HPP
#define PUGGO_POINT_LIGHT_COMPONENT_HPP

#include <LightComponent.hpp>

namespace puggo {
    class PointLightComponent : public LightComponent {
    public:
        PointLightComponent(void) noexcept;
        PointLightComponent(const PointLightComponent& pointLightComponent) noexcept;
        PointLightComponent(PointLightComponent&& pointLightComponent) noexcept;

        PointLightComponent& operator=(const PointLightComponent& pointLightComponent) noexcept;
        PointLightComponent& operator=(PointLightComponent&& pointLightComponent) noexcept;

        const float& getConstant(void) const noexcept;
        void setConstant(const float& constant) noexcept;

        const float& getLinear(void) const noexcept;
        void setLinear(const float& linear) noexcept;

        const float& getQuadratic(void) const noexcept;
        void setQuadratic(const float& quadratic) noexcept;

    private:
        float constant;
        float linear;
        float quadratic;
    };
}

#endif // !PUGGO_POINT_LIGHT_COMPONENT_HPP

