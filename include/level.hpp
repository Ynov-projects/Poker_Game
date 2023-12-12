#pragma once

#include <vector>
#include <SDL2/SDL_mixer.h>

#include "render_window.hpp"
#include "card.hpp"
#include "player.hpp"
#include "enemy.hpp"

class Level
{
    public:
        Level(RenderWindow &window, Mix_Music* music, Player& player);
        ~Level();
        void update();
        void render(RenderWindow &window);
        void resetGame(std::vector<Card> gameCards, std::vector<Card> enemyCards);

        std::vector<Card> getCards(){return cards;};
        int getTurn(){return turn;};
        int nextTurn(){return turn++;};
        Player& getPlayer(){return player;};
        Enemy& getEnemy(){return enemy;};

    private:
        RenderWindow &window;
        Mix_Music* music;
        std::vector<Card> cards;
        Player& player;
        Enemy enemy;
        int turn = 1;
};