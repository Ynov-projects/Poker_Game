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
        void removeCoins(int _coins);
        int getCoins(){return coins;};
        int getPlayedCoins(){return playedCoins;};
        int getFlatPlayedCoins(){return flatPlayedCoins;};

    private:
        EventManager &eventManager;
        std::vector<Card> cards{};
        int coins, playedCoins, flatPlayedCoins;
};