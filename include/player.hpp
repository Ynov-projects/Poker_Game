#pragma once

#include <vector>

#include "card.hpp"
#include "event_manager.hpp"

class Player
{
    public:
        Player(EventManager &_eventManager, int _coins);
        ~Player();
        std::vector<Card> getCards(){return cards;};
        void addCards(Card card);
        void clearCards(){cards = {};};

        char action();

        void addCoins(int coinNumber); // Limite de pièces fixé à 20
        void removeCoins(int _coins);
        int getCoins(){return coins;};
        int getPlayedCoins(){return playedCoins;};
        int getFlatPlayedCoins(){return flatPlayedCoins;};

        bool check(){return eventManager.getChecking();};
        bool fold(){return eventManager.getFolding();};
        bool bid(){return eventManager.getBidding();};
        bool nextGame(){return eventManager.getNextGame();};

    private:
        EventManager &eventManager;
        std::vector<Card> cards{};
        int coins, playedCoins, flatPlayedCoins;
};