#pragma once

#include <SDL2/SDL.h>

class EventManager
{
public:
    EventManager(){
        folded = false;
        keydown = false;
        lastKeyDownInSec = 0;
    };
    ~EventManager() = default; // Destructeur avec liste d'initialisation vide
    void processEvents(int newTime);
    void fold();

    bool isGameRunning() const { return gameRunning; }
    bool isFolded() const { return folded; }

private:
    SDL_Event event; // Structure qui contient le type d'évènement et ses données associées
    bool gameRunning{1};
    bool keydown;
    bool folded;
    int lastKeyDownInSec;
};