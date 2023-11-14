#pragma once

#include <vector>

#include "card.hpp"

class Player
{
    public:
        Player(){};
        ~Player(){std::cout << "Player détruit" << std::endl;};
        std::vector<Card> cards;
    
    private:
};