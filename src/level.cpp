#include <SDL2/SDL_mixer.h>
#include <stdlib.h>     /* srand, rand */
#include <vector>
#include <algorithm>

#include "level.hpp"
#include "constants.hpp"
#include "player.hpp"
#include "utils.hpp"
#include "enemy.hpp"

Level::Level( RenderWindow &window, Mix_Music* music, Player _player) : window(window), player(_player), enemy(5)
{
    turn = 1;
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
        player.addCards(card);
    }

    // Permet de donner les cartes qui seront le flop / le turn / la river
    for(int i = 0; i < 5; i++){
        int index = secs%allCards.size();
        Card card = allCards[index];
        allCards.erase(allCards.begin() + index);
        card.move(x + 20 * i, WINDOW_HEIGHT / 2 - CARD_HEIGHT / 2);
        cards.push_back(card);
    }

    // Distribution des cartes au enemy
    for(int i = 0; i < 2; i++){
        int index = secs%allCards.size();
        Card card = allCards[index];
        allCards.erase(allCards.begin() + index);
        card.move(x + 20 * i, WINDOW_HEIGHT / 2 + CARD_HEIGHT * 2);
        enemy.addCards(card);
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
    for(Card card : player.getCards())
    {
        window.render(card);
    }
    // Si on est au 2ème tour
    int cardNumber = 0;
    switch(turn){
        case 1:
            cardNumber = 5;
            break;
        case 2:
            cardNumber = 2;
            break;
        case 3:
            cardNumber = 1;
            break;
    }
    // std::cout << turn << " " << cards.size() << " " << cardNumber << std::endl;
    for(int i = 0; i < cards.size() - cardNumber; i++)
    {
        Card card = cards[i];
        window.render(card);
    }
    for(int i = 0; i < player.getCoins(); i++){
        int j = i / 5;
        Entity coin = Entity(Vector2f(250 - i%5 * 20, 160 - j*20), window.loadTexture(COIN_PATH), COIN_WIDTH, COIN_HEIGHT, std::make_pair(0, 0));
        window.render(coin);
    }
}

int Level::testAllCombinations(std::vector<Card> playerCards){
    std::vector<Card> allCards{};
    for(int i = 0; i < playerCards.size(); i++){
        allCards.push_back(playerCards[i]);
    } // On ajout les cartes du joueur
    for(int i = 0; i < cards.size(); i++){
        allCards.push_back(cards[i]);
    } // On ajoute les 5 cartes révélées

    /*
        Quinte flush royale -> 10 // Quinte flush -> 9 // Carré -> 8 // Full -> 7 // Couleur -> 6
        Quinte -> 5 // Brelan -> 4 // Deux paires -> 3 // Paire -> 2 // Carte la plus haute -> 1    
    */
    int score = testColor(allCards) == 0 ? testQuinte(allCards, 0) : testColor(allCards);
    std::cout << "score : " << score << std::endl;
    return score;
}

int Level::testColor(std::vector<Card> _cards){
    int families[]{0,0,0,0};
    for(Card card : _cards){
        families[card.getFamily()-1]++;
    }
    int max = *max_element(families, families + 4);
    if(max > 4){
        int royal = false;
        if(testQuinte(_cards, 1) == 5){
            for(Card card : _cards){
                royal += card.getValue() == 10 || card.getValue() == 1;
            }
            return royal > 1 ? 10 : 9;                      // Ici une quinte flush royale ou une quinte flush
        }
        return 4;                                           // Ici une couleur
    }
    return 0;                                               // Pas de couleur
}

int Level::testQuinte(std::vector<Card> _cards, bool color){
    std::vector<int> values{};
    for(Card card : _cards){
        values.push_back(card.getValue());
    }
	std::sort(values.begin(),values.end());

    for(int i =0; i<2; i++){
        bool suite = true;
        for(int j = 0; j < 4; j++){
            if(suite){
                suite = values[j+i+1] - values[j+i] == 1;
            }
        }
        if(suite) return 5;                                 // Ici une quinte
        if(color) return 0; // Couleur simple
    }
    
    std::vector<int> max = mostRepeatedValues(_cards);
    if(max[1] == 4){
        return 8;                                           // Ici un carré
    }else if(max[1] == 3){
        return testOtherPair(max[0], _cards) == 2 ? 7 : 4;  // Ici un full ou un brelan
    }else if(max[1] == 2){
        return testOtherPair(max[0], _cards) == 2 ? 3 : 2;  // Ici une double paire ou une paire
    }
    return 1;                                               // Ici la carte haute
}

int Level::testOtherPair(int value, std::vector<Card> _cards){
    for(int i = 0; i < _cards.size(); i++){
        if(_cards[i].getValue() == value){
            _cards.erase(_cards.begin() + i);
        }
    }
    std::vector<int> max = mostRepeatedValues(_cards);
    return max[1] >= 2 ? 2 : 1; // Double paire ou rien
}

std::vector<int> Level::mostRepeatedValues(std::vector<Card> _cards){
    std::vector<int> values{0,0,0,0,0,0,0,0,0,0,0,0,0};
    for(Card card : _cards){
        values[card.getValue()]++;
    }
    int index, max = 0;
    for(int i = 0; i < values.size(); i++){
        if(values[i] >= max){
            index = i;
            max = values[i];
        }
    }
    return std::vector<int>{index, max};
}