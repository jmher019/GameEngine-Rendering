#ifndef PUGGO_Z_INDEX_COMPONENT_HPP
#define PUGGO_Z_INDEX_COMPONENT_HPP

#include <glm\glm.hpp>

using namespace glm;

namespace puggo {
    constexpr float MIN_Z_INDEX = 0.f;
    constexpr float MAX_Z_INDEX = 1e6f;

    struct ZIndexComponent {
        float zIndex;
    };

    bool operator==(const ZIndexComponent& left, const ZIndexComponent& right) noexcept;
    float computeActualZIndex(const ZIndexComponent& zIndexComponent) noexcept;
}

#endif // !PUGGO_Z_INDEX_COMPONENT_HPP
