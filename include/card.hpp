#pragma once

#include <string>

#include "entity.hpp"
#include "event_manager.hpp"
#include "constants.hpp"

class Card : public Entity{
    public:
        Card(Vector2f p_pos, SDL_Texture *p_tex, std::pair<int, int> spriteSheetConfiguration, int _family, int _value)
        : Entity(p_pos, p_tex, CARD_WIDTH, CARD_HEIGHT, spriteSheetConfiguration){family = _family; value = _value;}
        int getFamily(){return family;}
        int getValue(){return value;}
    private:
        int family; // 1 : coeur / 2 : carreau / 3 : trèfle / 4 : pique
        int value; // 11 : valet / 12 : reine / 13 : roi
};