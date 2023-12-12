#pragma once

#include <vector>

#include "card.hpp"
#include "event_manager.hpp"

class Test
{
    public:
        int testAllCombinations(std::vector<Card> playerCards, std::vector<Card> gameCards);
        int testColor(std::vector<Card> _cards);
        int testQuinte(std::vector<Card> _cards, bool color);
        int testOtherPair(int value, std::vector<Card> _cards);
        std::vector<int> mostRepeatedValues(std::vector<Card> _cards);
};