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
        void addCoins(){coins += coins == 20 ? 0 : 1;}; // Limite de pièces fixé à 20
        bool removeCoins();
        int getCoins(){return coins;};

    private:
        EventManager &eventManager;
        std::vector<Card> cards{};
        int coins;
};