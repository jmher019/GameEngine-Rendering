#include <ColorComponent.hpp>

using namespace puggo;

bool puggo::operator==(const ColorComponent& left, const ColorComponent& right) noexcept {
    return left.fillColor == right.fillColor &&
        left.textColor == right.textColor;
}