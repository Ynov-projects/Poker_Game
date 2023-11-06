#pragma once

#include "render_window.hpp"
#include "entity.hpp"
#include "level.hpp"

class RenderManager
{
public:
    RenderManager(RenderWindow &window, Level &level);
    void render();

private:
    RenderWindow &window;
    Level &level;
};
