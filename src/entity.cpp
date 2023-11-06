#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "entity.hpp"

// Constructeur
Entity::Entity(Vector2f p_pos, SDL_Texture* p_tex, int frameWidth, int frameHeight,
std::pair<int, int> spriteSheetConfiguration)
    :pos(p_pos), tex(p_tex), currentFrame{0,0,frameWidth,frameHeight},
    spriteSheetConfiguration(spriteSheetConfiguration) {}

// Déplace l'entité
void Entity::move(float dx, float dy)
{
    pos.x += dx;
    pos.y += dy;
}

void Entity::updateAnimation()
{
    currentFrameCoordinates.first++;
    if(currentFrameCoordinates.first > spriteSheetConfiguration.first)
    {
        currentFrameCoordinates.first = 0;
        currentFrameCoordinates.second++;
        if(currentFrameCoordinates.second > spriteSheetConfiguration.second)
        {
            currentFrameCoordinates.second = 0;
        }
    }
    currentFrame.x = currentFrameCoordinates.first * currentFrame.w;
    currentFrame.y = currentFrameCoordinates.second * currentFrame.h;
}