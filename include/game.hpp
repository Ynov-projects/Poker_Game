#pragma once

#include "event_manager.hpp"
#include "update_manager.hpp"
#include "render_manager.hpp"
#include "render_window.hpp"
#include "level.hpp"
#include "player.hpp"

class Game
{
public:
    Game();
    ~Game();
    int run();
    Mix_Music* loadMusic(const char* filePath);
    int runAgain();

private:
    void cleanUp();

    float currentTime, accumulator{0.0f}, timeStep;
    RenderWindow window;
    EventManager eventManager;
    UpdateManager updateManager;
    RenderManager renderManager;
    Player player;
    Level level;
    int statusLevel{};
};
