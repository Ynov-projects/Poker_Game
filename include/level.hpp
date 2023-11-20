#pragma once

#include <vector>
#include <SDL2/SDL_mixer.h>

#include "render_window.hpp"
#include "card.hpp"
#include "player.hpp"

class Level
{
    public:
        Level(RenderWindow &window, Mix_Music* music, Player & player);
        ~Level();
        void update();
        void render(RenderWindow &window);
        std::vector<Card> getCards(){return cards;};
        int getTurn(){return turn;};
        void nextTurn(){turn++;std::cout << "coucou" << std::endl;};
    
    private:
        RenderWindow &window;
        Mix_Music* music;
        std::vector<Card> cards;
        Player player;
        int turn = 1;
};