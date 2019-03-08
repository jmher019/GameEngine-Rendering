#include <TextComponent.hpp>

bool puggo::operator==(const TextComponent& left, const TextComponent& right) noexcept {
    return left.fontFamily == right.fontFamily &&
        left.fontSize == right.fontSize &&
        left.text == right.text &&
        left.textAlign == right.textAlign &&
        left.textVerticalAlign == right.textVerticalAlign &&
        left.wordWrap == right.wordWrap;
}