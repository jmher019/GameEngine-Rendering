#ifndef PUGGO_SIZE_COMPONENT_HPP
#define PUGGO_SIZE_COMPONENT_HPP

namespace puggo {
    struct SizeComponent {
        float width = 0.f;
        float height = 0.f;
    };

    bool operator==(const SizeComponent& left, const SizeComponent& right) noexcept;
}

#endif // !PUGGO_SIZE_COMPONENT_HPP
