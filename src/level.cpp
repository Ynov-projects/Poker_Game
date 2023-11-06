#include <SDL2/SDL_mixer.h>

#include "level.hpp"
#include "constants.hpp"

Level::Level( RenderWindow &window, Mix_Music* music) : window(window)
{
    char valeurs[14] = {'1', '2', '3', '4', '5', '6', '7', '8', '9', '10', 'j', 'q', 'k', 'a'};
    char sigles[4] = {'c', 'k', 't', 'p'};
    for(int i = 0; i < sizeof(valeurs); i++)
    {
        for(int j = 0; j < sizeof(sigles); j++)
        cards.push_back(
            Card(Vector2f(0, 0), window.loadTexture(CARDS_PATH + valeurs[i] + sigles[j] + ".png"), std::make_pair(0, 0))
        );
    }

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
