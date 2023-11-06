#pragma once

#include <vector>
#include <SDL2/SDL_mixer.h>

#include "render_window.hpp"

class Level
{
    public:
        Level(RenderWindow &window, Mix_Music* music);
        ~Level();
        void update();
        void render(RenderWindow &window);
    
    private:
        RenderWindow &window;
        Mix_Music* music;
};