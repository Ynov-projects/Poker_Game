#pragma once

#include <vector>
#include <algorithm>

#include "utils.hpp"
#include "card.hpp"
#include "test.hpp"

int Test::testAllCombinations(std::vector<Card> playerCards, std::vector<Card> gameCards){
    std::vector<Card> allCards{};
    for(int i = 0; i < playerCards.size(); i++){
        allCards.push_back(playerCards[i]);
    } // On ajout les cartes du joueur
    for(int i = 0; i < gameCards.size(); i++){
        allCards.push_back(gameCards[i]);
    } // On ajoute les 5 cartes révélées
    /*
        Quinte flush royale -> 10 // Quinte flush -> 9 // Carré -> 8 // Full -> 7 // Couleur -> 6
        Quinte -> 5 // Brelan -> 4 // Deux paires -> 3 // Paire -> 2 // Carte la plus haute -> 1    
    */
    int score = testColor(allCards) == 0 ? testQuinte(allCards, 0) : testColor(allCards);
    std::cout << "score : " << score << std::endl;
    return score;
}

int Test::testColor(std::vector<Card> _cards){
    int families[]{0,0,0,0};
    for(Card card : _cards){
        families[card.getFamily()-1]++;
    }
    int max = *max_element(families, families + 4);
    if(max > 4){
        int royal = false;
        if(testQuinte(_cards, 1) == 5){
            for(Card card : _cards){
                royal += card.getValue() == 10 || card.getValue() == 1;
            }
            return royal > 1 ? 10 : 9;                      // Ici une quinte flush royale ou une quinte flush
        }
        return 4;                                           // Ici une couleur
    }
    return 0;                                               // Pas de couleur
}

int Test::testQuinte(std::vector<Card> _cards, bool color){
    std::vector<int> values{};
    for(Card card : _cards){
        values.push_back(card.getValue());
    }
	std::sort(values.begin(),values.end());

    for(int i =0; i<2; i++){
        bool suite = true;
        for(int j = 0; j < 4; j++){
            if(suite){
                suite = values[j+i+1] - values[j+i] == 1;
            }
        }
        if(suite) return 5;                                 // Ici une quinte
        if(color) return 0; // Couleur simple
    }
    
    std::vector<int> max = mostRepeatedValues(_cards);
    if(max[1] == 4){
        return 8;                                           // Ici un carré
    }else if(max[1] == 3){
        return testOtherPair(max[0], _cards) == 2 ? 7 : 4;  // Ici un full ou un brelan
    }else if(max[1] == 2){
        return testOtherPair(max[0], _cards) == 2 ? 3 : 2;  // Ici une double paire ou une paire
    }
    return 1;                                               // Ici la carte haute
}

int Test::testOtherPair(int value, std::vector<Card> _cards){
    for(int i = 0; i < _cards.size(); i++){
        if(_cards[i].getValue() == value){
            _cards.erase(_cards.begin() + i);
        }
    }
    std::vector<int> max = mostRepeatedValues(_cards);
    return max[1] >= 2 ? 2 : 1; // Double paire ou rien
}

std::vector<int> Test::mostRepeatedValues(std::vector<Card> _cards){
    std::vector<int> values{0,0,0,0,0,0,0,0,0,0,0,0,0};
    for(Card card : _cards){
        values[card.getValue()]++;
    }
    int index, max = 0;
    for(int i = 0; i < values.size(); i++){
        if(values[i] >= max){
            index = i;
            max = values[i];
        }
    }
    return std::vector<int>{index, max};
}