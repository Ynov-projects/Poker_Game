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
        char action();
        void addCoins(int coinNumber); // Limite de pièces fixé à 20
        bool removeCoins();
        int getCoins(){return coins;};
        int getPlayedCoins(){return playedCoins;};

    private:
        EventManager &eventManager;
        std::vector<Card> cards{};
        int coins, playedCoins;
};