#ifndef PUGGO_COLOR_COMPONENT_HPP
#define PUGGO_COLOR_COMPONENT_HPP

#include <glm/glm.hpp>

using namespace glm;

namespace puggo {
    struct ColorComponent {
        vec4 fillColor = vec4(1.f, 1.f, 1.f, 1.f);
        vec4 textColor = vec4(0.f, 0.f, 0.f, 1.f);
    };

    bool operator==(const ColorComponent& left, const ColorComponent& right) noexcept;
}

#endif // !PUGGO_COLOR_COMPONENT_HPP
