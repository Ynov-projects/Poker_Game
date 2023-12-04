#pragma once

#include <SDL2/SDL.h>

class EventManager
{
public:
    EventManager(){
        checking = false;
        folding = false;
        bidding = false;
        lastKeyDownInSec = 0;
    };
    ~EventManager() = default; // Destructeur avec liste d'initialisation vide
    void processEvents(int newTime);
    bool isGameRunning() const { return gameRunning; }
    bool getFolding(){return folding;};
    bool getBidding(){return bidding;};
    bool getChecking(){return checking;};

private:
    SDL_Event event; // Structure qui contient le type d'évènement et ses données associées
    bool gameRunning{1};
    bool checking = false;
    bool folding = false;
    bool bidding = false;
    int lastKeyDownInSec;
};