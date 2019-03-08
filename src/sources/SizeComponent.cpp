#include <SizeComponent.hpp>

using namespace puggo;

bool puggo::operator==(const SizeComponent& left, const SizeComponent& right) noexcept {
    return left.height == right.height && left.width == right.width;
}