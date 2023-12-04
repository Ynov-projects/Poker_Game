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
        Level(RenderWindow &window, Mix_Music* music, Player player);
        ~Level();
        void update();
        void render(RenderWindow &window);
        void resetGame();

        std::vector<Card> getCards(){return cards;};
        int getTurn(){return turn;};
        int nextTurn(){return turn++;};
        Player& getPlayer(){return player;};
        Enemy& getEnemy(){return enemy;};

        bool check(){return player.action() == 'c';};
        bool fold(){return player.action() == 'f';};
        bool bid(){return player.action() == 'b';};
        bool nextGame(){return player.action() == 'n';};

        void removeCoins(int _coins){player.removeCoins(_coins);};
        void addCoins(int _coins){player.addCoins(_coins);};
        int getFlatPlayedCoins(){return player.getFlatPlayedCoins();};
        int getPlayedCoins(){return player.getPlayedCoins();};
        int getCoins(){return player.getCoins();};

        int testAllCombinations(std::vector<Card> playerCards);
        int testColor(std::vector<Card> _cards);
        int testQuinte(std::vector<Card> _cards, bool color);
        int testOtherPair(int value, std::vector<Card> _cards);
        std::vector<int> mostRepeatedValues(std::vector<Card> _cards);
    
    private:
        RenderWindow &window;
        Mix_Music* music;
        std::vector<Card> cards;
        Player player;
        Enemy enemy;
        int turn = 1;
};