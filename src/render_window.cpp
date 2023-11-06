#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

#include "render_window.hpp"
#include "entity.hpp"
#include "constants.hpp"

// Cette fonction est appelée lors de la création d'un objet RenderWindow
RenderWindow::RenderWindow()
    : window(SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN)),
      renderer(SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC))
// SDL_CreateRenderer sert à créer un renderer (un moteur de rendu)
// SDL_RENDERER_PRESENTVSYNC sert à synchroniser le rendu avec le rafraîchissement de l'écran
{
    if (window == nullptr)
    {
        std::cout << "Window failed to init. Error: " << SDL_GetError() << std::endl;
    }
    if (renderer == nullptr)
    {
        std::cout << "Renderer failed to init. Error: " << SDL_GetError() << std::endl;
    }
}

SDL_Texture *RenderWindow::loadTexture(const char *file_path)
{
    SDL_Texture *texture = nullptr; // Utilisation de nullptr au lieu de NULL
    texture = IMG_LoadTexture(renderer, file_path);


    if (texture == nullptr) // Utilisation de nullptr au lieu de NULL
        std::cout << "Failed to load texture. Error: " << SDL_GetError() << std::endl;


    return texture;
}

// Clean up est appelé dans le destructeur de Game avant IMG_Quit et SDL_Quit
// car la fenêtre et le renderer doivent être nettoyés avant de quitter SDL
void RenderWindow::cleanUp()
{
    SDL_DestroyRenderer(renderer); // Nettoyage du renderer
    SDL_DestroyWindow(window);     // Nettoyage de la fenêtre
}

// Cette fonction sert à effacer le renderer
void RenderWindow::clear()
{
    SDL_RenderClear(renderer); // Efface le renderer
}

// Cette fonction sert à afficher une texture
void RenderWindow::render(Entity &p_entity)
{
    SDL_Rect src;                         // Création d'un rectangle source, à partir de la texture originale
    src.x = p_entity.getCurrentFrame().x; // Position x du rectangle
    src.y = p_entity.getCurrentFrame().y; // Position y du rectangle
    src.w = p_entity.getCurrentFrame().w; // Largeur du rectangle
    src.h = p_entity.getCurrentFrame().h; // Hauteur du rectangle

    SDL_Rect dst;                             // Création d'un rectangle destination (où la texture sera affichée)
    dst.x = p_entity.getPos().x * SCALE_FACTOR;          // Position x du rectangle avec un facteur d'échelle de 4
    dst.y = p_entity.getPos().y * SCALE_FACTOR;          // Position y du rectangle avec un facteur d'échelle de 4
    dst.w = p_entity.getCurrentFrame().w * SCALE_FACTOR; // Largeur du rectangle avec un facteur d'échelle de 4
    dst.h = p_entity.getCurrentFrame().h * SCALE_FACTOR; // Hauteur du rectangle avec un facteur d'échelle de 4

    SDL_RenderCopy(renderer, p_entity.getTex(), &src, &dst); // Affiche la texture dans le renderer
}

// Cette fonction sert à afficher le renderer
void RenderWindow::display()
{
    SDL_RenderPresent(renderer); // Affiche le renderer
}