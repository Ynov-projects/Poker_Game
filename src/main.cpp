#include <iostream>
#include <SDL2/SDL_mixer.h>
#include "game.hpp"

bool initSDL()
{
    // Initialisation de SDL Audio
    if (SDL_Init(SDL_INIT_AUDIO) < 0)
    {
        std::cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    // Initialisation de SDL2
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
        return false;
    }

    // Initialisation de SDL2_image
    if (!(IMG_Init(IMG_INIT_PNG)))
    {
        std::cout << "IMG_Init Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return false;
    }

    // Initialisation de SDL_mixer
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
    {
        std::cout << "SDL_mixer could not initialize! SDL_mixer Error: " << Mix_GetError() << std::endl;
        return false;
    }

    return true;
}

// Fonction principale du jeu
int runGame()
{
    // On initialise SDL2 et SDL2_image anvant de créer une instance de Game
    // car la classe Game utilise des types de SDL2 et SDL2_image
    if (!initSDL())
        return 1;

    Game game; // Crée une instance du jeu avec les constantes globales
    game.run(); // Exécute le jeu

    return 0;
}

// Fonction principale du programme
int main(int argc, char *argv[])
{
    return runGame();
}