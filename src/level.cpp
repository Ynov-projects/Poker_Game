#include <SDL2/SDL_mixer.h>
#include <stdlib.h>     /* srand, rand */

#include "level.hpp"
#include "constants.hpp"
#include "player.hpp"
#include "utils.hpp"

Level::Level( RenderWindow &window, Mix_Music* music, Player &_player) : window(window), player(_player)
{
    int secs = utils::hireTimeInMilliSeconds();
    char valeurs[14] = {'a', '2', '3', '4', '5', '6', '7', '8', '9', '10', 'j', 'q', 'k'};
    char sigles[4] = {'c', 'k', 't', 'p'};
    std::vector<Card> allCards;
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
        card.move(x + 20 * i, WINDOW_HEIGHT / 2 + CARD_HEIGHT * 2);
        player.cards.push_back(card);
    }

    // Permet de donner les cartes qui seront le flop / le turn / la river
    for(int i = 0; i < 5; i++){
        int index = secs%allCards.size();
        Card card = allCards[index];
        allCards.erase(allCards.begin() + index);
        card.move(x + 20 * i, WINDOW_HEIGHT / 2 - CARD_HEIGHT / 2);
        cards.push_back(card);
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
    // if(player.getAction() == 1){
    //     nextTurn();
    // }
}

void Level::render(RenderWindow &window)
{
    for(Card card : player.cards)
    {
        window.render(card);
    }
    // Si on est au 2ème tour
    int cardNumber = turn == 1 ? 2 : turn <= 2 ? 1 : 0;

    for(int i = 0; i < cards.size() - cardNumber; i++)
    {
        Card card = cards[i];
        window.render(card);
    }
}
