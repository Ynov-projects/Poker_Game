#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "math.hpp"

class Entity
{
public:
    Entity(Vector2f p_pos, SDL_Texture* p_tex, int frameWidth, int frameHeight, 
    std::pair<int, int> spriteSheetConfiguration); // Constructeur
    void move(float dx, float dy);  // Déplace l'entité
    bool isCollidingWith(const Entity &other) const;
    void updateAnimation();

    Vector2f& getPos(){return pos;};
    SDL_Texture* getTex(){return tex;}; // Retourne la texture
    void setTex(SDL_Texture* p_tex){tex = p_tex;}; // Retourne la texture
    SDL_Rect getCurrentFrame(){return currentFrame;}; // Retourne le rectangle courant

private:
    Vector2f pos;
    SDL_Rect currentFrame; // Rectangle (cadre) où la texture sera affichée
    SDL_Texture* tex; // Texture

    std::pair<int, int> spriteSheetConfiguration{0, 0};
    std::pair<int, int> currentFrameCoordinates{0, 0};
};
