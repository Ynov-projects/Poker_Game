#pragma once

#include <vector>

#include "card.hpp"
#include "event_manager.hpp"

class Player
{
    public:
        Player(EventManager &_eventManager);
        ~Player();
        std::vector<Card> getCards(){return cards;};
        void addCards(Card card);
        char action();
        void addCoins(int _coins){coins += _coins;};
        void removeCoins(int _coins){coins -= _coins;};
        int getCoins(){return coins;};

    private:
        EventManager &eventManager;
        std::vector<Card> cards{};
        int coins = 5;
};