#include <ZIndexComponent.hpp>

using namespace puggo;

bool puggo::operator==(const ZIndexComponent& left, const ZIndexComponent& right) noexcept {
    return left.zIndex == right.zIndex;
}

float puggo::computeActualZIndex(const ZIndexComponent& zIndexComponent) noexcept {
    return -clamp(zIndexComponent.zIndex, MIN_Z_INDEX, MAX_Z_INDEX);
}