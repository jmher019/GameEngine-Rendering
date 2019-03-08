#ifndef PUGGO_TEXT_COMPONENT_HPP
#define PUGGO_TEXT_COMPONENT_HPP

#include <string>

#include <glm/glm.hpp>

using namespace std;
using namespace glm;

namespace puggo {
    enum class FontFamily {
        ARIAL
    };

    enum class TextAlign {
        LEFT,
        CENTER,
        RIGHT
    };

    enum class TextVerticalAlign {
        TOP,
        CENTER,
        BOTTOM
    };

    struct TextComponent {
        float fontSize = 0.f;
        string text = string("");
        FontFamily fontFamily = FontFamily::ARIAL;
        TextAlign textAlign = TextAlign::LEFT;
        TextVerticalAlign textVerticalAlign = TextVerticalAlign::TOP;
        bool wordWrap = false;
    };

    bool operator==(const TextComponent& left, const TextComponent& right) noexcept;
}

#endif // !PUGGO_TEXT_COMPONENT_HPP
