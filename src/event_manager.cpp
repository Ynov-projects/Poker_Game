#include "event_manager.hpp"

#include <iostream>

void EventManager::processEvents(int newTime)
{
    if(newTime - lastKeyDownInSec > 2){
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                gameRunning = false;
                break;
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym)
                {
                    case SDLK_z:
                        // moveUp = true; // Active le mouvement vers le haut
                        break;
                    case SDLK_q:
                        // moveLeft = true; // Active le mouvement vers la gauche
                        break;
                    case SDLK_s:
                        // moveDown = true; // Active le mouvement vers le bas
                        break;
                    case SDLK_d:
                        // moveRight = true; // Active le mouvement vers la droite
                        break;
                    case SDLK_SPACE:
                        std::cout << "keydown : " << keydown << std::endl;
                        if(keydown == false){
                            folded = true; // Indique que la barre d'espace a été enfoncée
                            keydown = true;
                            lastKeyDownInSec = newTime;
                        }
                        break;
                }
                break;
            }
        }
    }else{
        folded = false; // Indique que la barre d'espace a été enfoncée
        keydown = false;
    }
}

void EventManager::fold(){
    folded = false;
}