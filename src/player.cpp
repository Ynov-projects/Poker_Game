#pragma once

#include <vector>

#include "card.hpp"
#include "player.hpp"
#include "event_manager.hpp"

Player::Player(EventManager &_eventManager, int _coins) : eventManager(_eventManager){coins = _coins; playedCoins = _coins;}

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
    }else if(eventManager.getNextGame()){
        return 'n';
    }
    return 'w';
}

bool Player::removeCoins(){
    coins -= 1;
    playedCoins += 1;
    return coins > 0;
}

void Player::addCoins(int coinNumber){
    coins += coinNumber;
    coins -= coins >= 20 ? coins - 20 : 0;
    playedCoins = 0;
}