#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "entity.hpp"

class RenderWindow
{
public:
    RenderWindow(); // Constructeur avec des noms de paramètres plus clairs
    // Nous ne définissons pas de destructeur car la fenêtre et le renderer doivent être
    // nettoyés dans le destructeur de Game avant IMG_Quit et SDL_Quit
    SDL_Texture* loadTexture(const char* p_filePath); // Charge une texture
    void cleanUp(); // Nettoie la mémoire
    void clear(); // Efface le renderer
    void render(Entity& p_entity); // Affiche une texture
    void display(); // Affiche le renderer

private:
    SDL_Window* window{nullptr};  // Initialisation à nullptr
    SDL_Renderer* renderer{nullptr};  // Initialisation à nullptr
};
