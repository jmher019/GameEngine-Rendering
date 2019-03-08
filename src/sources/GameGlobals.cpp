#include <GameGlobals.hpp>

using namespace puggo;

GameGlobals::GameGlobals(void) noexcept {}

const mat4& GameGlobals::getProjection(void) noexcept {
    return projection;
}

void GameGlobals::setProjection(const mat4& projection) noexcept {
    GameGlobals::projection = projection;
}

const mat4& GameGlobals::getView(void) noexcept {
    return view;
}

void GameGlobals::setView(const mat4& view) noexcept {
    GameGlobals::view = view;
}

const mat4& GameGlobals::getUIProjection(void) noexcept {
    return uiProjection;
}

void GameGlobals::setUIProjection(const mat4& uiProjection) noexcept {
    GameGlobals::uiProjection = uiProjection;
}