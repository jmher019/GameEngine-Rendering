#ifndef PUGGO_GAME_GLOBALS_HPP
#define PUGGO_GAME_GLOBALS_HPP

#include <glm/glm.hpp>

using namespace glm;

namespace puggo {
    class GameGlobals {
    public:
        GameGlobals(const GameGlobals&) = delete;
        GameGlobals(GameGlobals&&) = delete;
        GameGlobals& operator=(const GameGlobals&) = delete;
        GameGlobals& operator=(GameGlobals&&) = delete;

        static const mat4& getProjection(void) noexcept;
        static void setProjection(const mat4& projection) noexcept;
        static const mat4& getView(void) noexcept;
        static void setView(const mat4& view) noexcept;
        static const mat4& getUIProjection(void) noexcept;
        static void setUIProjection(const mat4& uiProjection) noexcept;

    private:
        GameGlobals(void) noexcept;

        static mat4 projection;
        static mat4 view;
        static mat4 uiProjection;
    };
}

#endif // !PUGGO_GAME_GLOBALS_HPP
