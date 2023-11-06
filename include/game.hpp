#pragma once

#include "event_manager.hpp"
#include "update_manager.hpp"
#include "render_manager.hpp"
#include "render_window.hpp"
#include "level.hpp"

class Game
{
public:
    Game();
    ~Game();
    void run();
    Mix_Music* loadMusic(const char* filePath);

private:
    void cleanUp();

    float currentTime, accumulator{0.0f}, timeStep;
    RenderWindow window;
    EventManager eventManager;
    UpdateManager updateManager;
    RenderManager renderManager;
    Level level;
};
