#include <SDL2/SDL_mixer.h>
#include "game.hpp"
#include "utils.hpp"
#include "constants.hpp"
#include "test.hpp"

#include <iostream>

// Constructeur
Game::Game()
    : currentTime(utils::hireTimeInSeconds()),
      timeStep(TIME_STEP),
      window(),
      eventManager(),
      updateManager(eventManager, level),
      renderManager(window, level),
      player(eventManager, 7),
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
        if(player.check()){
            if(level.getTurn() < 4) level.nextTurn();

        }else if(player.bid()){
            if(level.getTurn() < 4) player.removeCoins(4-level.getTurn());

        }else if(player.fold()){
            player.addCoins(player.getFlatPlayedCoins() / 2);
            if(runAgain()) return 0; // Une nouvelle partie peut reprendre

        }else if(player.nextGame()){
            if(level.getTurn()==4){
                Test test;
                int enemyScore = test.testAllCombinations(level.getEnemy().getCards(), level.getCards());
                int playerScore = test.testAllCombinations(player.getCards(), level.getCards());

                if(enemyScore < playerScore){
                    player.addCoins(player.getPlayedCoins());
                }else if(enemyScore == playerScore){
                    player.addCoins(player.getFlatPlayedCoins());
                }
                player.addCoins(0);
                if(runAgain()) return 0; // Une nouvelle partie peut reprendre mais calcul des scores et des gains d'abord
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

int Game::runAgain(){
    if(player.getCoins() == 0) return 0;

    int secs = utils::hireTimeInMilliSeconds();
    char valeurs[14] = {'a', '2', '3', '4', '5', '6', '7', '8', '9', '10', 'j', 'q', 'k'};
    char sigles[4] = {'c', 'k', 't', 'p'};
    std::vector<Card> allCards{};
    for(int i = 0; i < sizeof(valeurs) - 1; i++)
    {
        for(int j = 0; j < sizeof(sigles); j++){
        allCards.push_back(
            Card(Vector2f(-400, -300), window.loadTexture((CARDS_PATH + std::string(1, valeurs[i]) + sigles[j] + ".png").c_str()), std::make_pair(0, 0), j + 1, i + 1)
        );
        }
    }

    int x = WINDOW_WIDTH / 2 - CARD_WIDTH * 3;
    
    // Distribution des cartes au joueur
    for(int i = 0; i < 2; i++){
        int index = secs%allCards.size();
        Card card = allCards[index];
        allCards.erase(allCards.begin() + index);
        card.move(x + 20 * (i-3), WINDOW_HEIGHT / 2 + CARD_HEIGHT * 2);
        player.addCards(card);
    }

    std::vector<Card> gameCards, enemyCards{};
    // Permet de donner les cartes qui seront le flop / le turn / la river
    for(int i = 0; i < 5; i++){
        int index = secs%allCards.size();
        Card card = allCards[index];
        allCards.erase(allCards.begin() + index);
        card.move(x + 20 * i, WINDOW_HEIGHT / 2 - CARD_HEIGHT / 2);
        gameCards.push_back(card);
    }

    // Distribution des cartes au enemy
    for(int i = 0; i < 2; i++){
        int index = secs%allCards.size();
        Card card = allCards[index];
        allCards.erase(allCards.begin() + index);
        card.move(x + 20 * (i+1), WINDOW_HEIGHT / 2 + CARD_HEIGHT * 2);
        enemyCards.push_back(card);
    }
    level.resetGame(gameCards, enemyCards);
    run();
}