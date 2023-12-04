#pragma once

#include <vector>

#include "card.hpp"
#include "player.hpp"
#include "event_manager.hpp"

Player::Player(EventManager &_eventManager, int _coins) : eventManager(_eventManager){coins = _coins;}

Player::~Player(){
    std::cout << "destroyed" << std::endl;
}

void Player::addCards(Card card){
    cards.push_back(card);
}

char Player::action(){
    if(eventManager.getFolding()){
        return 'f';
    }else if(eventManager.getChecking()){
        return 'c';
    }else if(eventManager.getBidding()){
        return 'b';
    }
    return 'w';
}

bool Player::removeCoins(){
    coins -= 1;
    return coins > 0;
}