#include <SDL2/SDL_mixer.h>
#include <stdlib.h>     /* srand, rand */
#include <vector>

#include "level.hpp"
#include "constants.hpp"
#include "enemy.hpp"

Level::Level( RenderWindow &window, Mix_Music* music, Player& _player) : window(window), player(_player), enemy(5)
{
    // Joue la musique en boucle car le second paramètre est égal à -1
    if (Mix_PlayMusic(music, -1) == -1)
    {
        std::cerr << "Failed to play music! SDL_mixer Error: " << Mix_GetError() << std::endl;
    }
}

void Level::resetGame(std::vector<Card> gameCards, std::vector<Card> enemyCards){
    turn = 1;
    cards = gameCards;
    for(Card c : enemyCards){
        enemy.addCards(c);
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
    for(Card card : player.getCards()) window.render(card);

    // Si on est au 2ème tour
    if(turn >= 2){
        window.render(cards[0]);
        window.render(cards[1]);
        window.render(cards[2]);
        if(turn >= 3){
            window.render(cards[3]);
            if(turn == 4){
                for(Card c : enemy.getCards()) window.render(c);
                window.render(cards[4]);
            }
        }
    }

    for(int i = 0; i < player.getCoins(); i++){
        int j = i / 10;
        Entity coin = Entity(Vector2f(250 - i%10 * 10, 160 - j*20), window.loadTexture(COIN_PATH), COIN_WIDTH, COIN_HEIGHT, std::make_pair(0, 0));
        window.render(coin);
    }
}