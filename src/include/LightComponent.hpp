#ifndef PUGGO_LIGHT_COMPONENT_HPP
#define PUGGO_LIGHT_COMPONENT_HPP

#include <glm/glm.hpp>

using namespace glm;
using namespace std;

namespace puggo {
    class LightComponent {
    public:
        const vec3& getAmbient(void) const noexcept;
        void setAmbient(const vec3& ambient) noexcept;

        const vec3& getDiffuse(void) const noexcept;
        void setDiffuse(const vec3& diffuse) noexcept;

        const vec3& getSpecular(void) const noexcept;
        void setSpecular(const vec3& specular) noexcept;

    protected:
        LightComponent(void) noexcept;
        LightComponent(const LightComponent& lightComponent) noexcept;
        LightComponent(LightComponent&& lightComponent) noexcept;

        LightComponent& operator=(const LightComponent& lightComponent) noexcept;
        LightComponent& operator=(LightComponent&& lightComponent) noexcept;

    private:
        vec3 ambient;
        vec3 diffuse;
        vec3 specular;
    };
}

#endif // !PUGGO_LIGHT_COMPONENT_HPP
