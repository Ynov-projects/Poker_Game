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
    while (eventManager.isGameRunning())
    {
        // Calcul des frames de logique de jeu par rapport aux frames de rendu
        float newTime = utils::hireTimeInSeconds();
        float frameTime = newTime - currentTime;
        currentTime = newTime;
        accumulator += frameTime;
        eventManager.processEvents(newTime);

        // Gestion des différentes actions faites par le joueur
        if(level.check()){
            std::cout << "coucou on check" << std::endl;
            if(level.nextTurn()==4){
                bool reussi = level.testAllCombinations(level.getEnemy().getCards()) > level.testAllCombinations(level.getPlayer().getCards()); 
                std::cout << reussi << std::endl;
                // return 2; // Une nouvelle partie peut reprendre mais calcul des scores et des gains d'abord
            }
        
        }else if(level.bid()){
            std::cout << "gros bide" << std::endl;
            if(!level.removeCoins()){
                return 1; // Le jeu est terminé, car le joueur n'a plus de pièces
            }
        }else if(level.fold()){
            std::cout << "oh le fold" << std::endl;
            return 2; // Une nouvelle partie peut reprendre
        }

        while (accumulator >= timeStep)
        {
            updateManager.update();
            accumulator -= timeStep;
            
        }

        renderManager.render();
    }
}

int Game::valueToBeat(){
    int secs = utils::hireTimeInMilliSeconds();
    std::cout << secs << std::endl;
    if(secs%701)return 10;
    if(secs%401)return 9;
    if(secs%301)return 8;
    if(secs%101)return 7;
    if(secs%51)return 6;
    if(secs%25)return 5;
    if(secs%15)return 4;
    if(secs%5)return 3;
    if(secs%3)return 2;
    return 1;
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