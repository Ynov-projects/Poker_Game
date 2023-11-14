#pragma once

#include <vector>
#include <SDL2/SDL_mixer.h>

#include "render_window.hpp"
#include "card.hpp"
#include "player.hpp"

class Level
{
    public:
        Level(RenderWindow &window, Mix_Music* music);
        ~Level();
        void update();
        void render(RenderWindow &window);
        Player getPlayer(){return player;};
        std::vector<Card> getCards(){return cards;};
    
    private:
        RenderWindow &window;
        Mix_Music* music;
        std::vector<Card> cards;
        Player player;
};