#include <SDL2/SDL_mixer.h>

#include "level.hpp"
#include "constants.hpp"

Level::Level( RenderWindow &window, Mix_Music* music) : window(window)
{
    // Joue la musique en boucle car le second paramètre est égal à -1
    if (Mix_PlayMusic(music, -1) == -1)
    {
        std::cerr << "Failed to play music! SDL_mixer Error: " << Mix_GetError() << std::endl;
    }
}

Level::~Level()
{
    Mix_HaltMusic();      // Arrête la musique
    Mix_FreeMusic(music); // Libère la mémorie allouée à la musique
}

void Level::update()
{
    
}

void Level::render(RenderWindow &window)
{

}
