#pragma once

#include <SDL2/SDL.h>

class EventManager
{
public:
    EventManager() = default; // Constructeur avec liste d'initialisation vide
    ~EventManager() = default; // Destructeur avec liste d'initialisation vide
    void processEvents();

    bool isMoveUpPressed() const { return moveUp; }
    bool isMoveDownPressed() const { return moveDown; }
    bool isMoveLeftPressed() const { return moveLeft; }
    bool isMoveRightPressed() const { return moveRight; }
    bool isSpaceBarPressed() const { return spaceBarPressed; }
    bool isGameRunning() const { return gameRunning; }

private:
    SDL_Event event; // Structure qui contient le type d'évènement et ses données associées
    bool gameRunning{true};
    bool moveUp{false}, moveLeft{false}, moveDown{false}, moveRight{false}, spaceBarPressed{false};
};