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
        //char getAction(){return action;};
        //void update();

    private:
        EventManager &eventManager;
        std::vector<Card> cards;
        //char action;
};