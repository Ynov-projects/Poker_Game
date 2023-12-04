#pragma once

#include <vector>

#include "card.hpp"
#include "enemy.hpp"
#include "event_manager.hpp"

Enemy::~Enemy(){
    std::cout << "destroyed" << std::endl;
}

void Enemy::addCards(Card card){
    cards.push_back(card);
}

bool Enemy::removeCoins(){
    coins -= 1;
    return coins > 0;
}