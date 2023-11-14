#pragma once

#include <vector>

#include "card.hpp"
#include "player.hpp"

Player::~Player(){
    std::cout << "destroyed" << std::endl;
}