#pragma once

#include <vector>

#include "card.hpp"
#include "player.hpp"
#include "event_manager.hpp"

Player::Player(EventManager &_eventManager) : eventManager(_eventManager){}

Player::~Player(){
    std::cout << "destroyed" << std::endl;
}

void Player::addCards(Card card){
    cards.push_back(card);
}

char Player::action(){
    return eventManager.action();
}