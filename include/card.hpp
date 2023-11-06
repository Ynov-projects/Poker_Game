#pragma once

#include <string>

#include "entity.hpp"
#include "event_manager.hpp"
#include "constants.hpp"

class Card : public Entity{
    public:
        Card();
        Card(Vector2f p_pos, SDL_Texture *p_tex, EventManager &p_EventManager,
            std::pair<int, int> spriteSheetConfiguration)
            : Entity(p_pos, p_tex, CARD_WIDTH, CARD_HEIGHT, spriteSheetConfiguration),
            eventManager(p_EventManager)
            {}
    private:
        EventManager &eventManager;
        string name;
};