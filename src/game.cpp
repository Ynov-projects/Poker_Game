#include <SDL2/SDL_mixer.h>
#include "game.hpp"
#include "utils.hpp"
#include "constants.hpp"

#include <iostream>

// Constructeur
Game::Game()
    : currentTime(utils::hireTimeInSeconds()),
      timeStep(TIME_STEP),
      window(),
      eventManager(),
      updateManager(eventManager, level),
      renderManager(window, level),
      player(eventManager, 3),
      level(window, loadMusic(LEVEL_MUSIC_PATH), player)
{}

// Destructeur
Game::~Game()
{
    cleanUp();
}


int Game::run()
{
    Player playerLevel = level.getPlayer();
    while (eventManager.isGameRunning())
    {
        // Calcul des frames de logique de jeu par rapport aux frames de rendu
        float newTime = utils::hireTimeInSeconds();
        float frameTime = newTime - currentTime;
        currentTime = newTime;
        accumulator += frameTime;
        eventManager.processEvents(newTime);

        if(level.getTurn() == 1 && level.getPlayer().getCoins() == 0) return 0;

        // Gestion des différentes actions faites par le joueur
        if(level.check()){
            if(level.getTurn() < 4) level.nextTurn();

        }else if(level.bid()){
            level.removeCoins(4-level.getTurn());

        }else if(level.fold()){
            std::cout << level.getFlatPlayedCoins() << std::endl;
            level.addCoins(level.getFlatPlayedCoins() / 2);
            runAgain(); // Une nouvelle partie peut reprendre

        }else if(level.nextGame()){
            if(level.getTurn()==4){
                int enemyScore = level.testAllCombinations(level.getEnemy().getCards());
                int playerScore = level.testAllCombinations(playerLevel.getCards());

                if(enemyScore < playerScore){
                    level.addCoins(level.getPlayedCoins());
                }else if(enemyScore == playerScore){
                    level.addCoins(level.getFlatPlayedCoins());
                }
                runAgain(); // Une nouvelle partie peut reprendre mais calcul des scores et des gains d'abord
            }
        }

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

void Game::runAgain(){
    level.resetGame();
    run();
}