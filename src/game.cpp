#include <SDL2/SDL_mixer.h>
#include "game.hpp"
#include "utils.hpp"
#include "constants.hpp"

// Constructeur
Game::Game()
    : currentTime(utils::hireTimeInSeconds()),
      timeStep(TIME_STEP),
      window(),
      eventManager(),
      player(),
      level(window, loadMusic(LEVEL_MUSIC_PATH), player),
      updateManager(eventManager, level),
      renderManager(window, level)
{}

// Destructeur
Game::~Game()
{
    cleanUp();
}


void Game::run()
{
    while (eventManager.isGameRunning())
    {
        // Calcul des frames de logique de jeu par rapport aux frames de rendu
        float newTime = utils::hireTimeInSeconds();
        float frameTime = newTime - currentTime;
        currentTime = newTime;
        accumulator += frameTime;
        eventManager.processEvents(); // Gestion des événements
        while (accumulator >= timeStep)
        {
            updateManager.update();
            accumulator -= timeStep;
            
        }

        renderManager.render();
    }
}


void Game::cleanUp()
{
    Mix_CloseAudio();
    window.cleanUp();
    IMG_Quit();
    SDL_Quit();
}

Mix_Music* Game::loadMusic(const char* filePath)
{
    Mix_Music* music = Mix_LoadMUS(filePath);
    if(!music)
    {
        std::cerr << "Failed to load music! SDL_mixer Error: " << Mix_GetError() << std::endl;
    }
    return music;
}