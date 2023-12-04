#pragma once

#include <vector>

#include "card.hpp"

class Enemy
{
    public:
        Enemy(int _coins){coins = _coins;};
        ~Enemy();
        std::vector<Card> getCards(){return cards;};
        void addCards(Card card);
        void addCoins(){coins += coins == 20 ? 0 : 1;}; // Limite de pièces fixé à 20
        bool removeCoins();
        int getCoins(){return coins;};

    private:
        std::vector<Card> cards{};
        int coins;
};