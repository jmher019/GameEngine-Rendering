#ifndef PUGGO_TRANSFORM2D_COMPONENT_HPP
#define PUGGO_TRANSFORM2D_COMPONENT_HPP

#include <Transform2D.hpp>

namespace puggo {
    struct Transform2DComponent {
        Transform2D localTransform;
        Transform2D globalTransform;

        void updateGlobalTransform(const Transform2D& parentTransform) noexcept;
    };

    bool operator==(const Transform2DComponent& left, const Transform2DComponent& right) noexcept;
}

#endif // !PUGGO_TRANSFORM2D_COMPONENT_HPP
