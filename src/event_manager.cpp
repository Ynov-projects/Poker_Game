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
                    case SDLK_f:
                        folding = true; // Quitte la main
                        lastKeyDownInSec = newTime;
                        break;
                    case SDLK_b:
                        bidding = true; // Mise 10% de la somme restante
                        lastKeyDownInSec = newTime;
                        break;
                    case SDLK_SPACE:
                        checking = true; // Continue la main
                        lastKeyDownInSec = newTime;
                        break;
                }
                break;
            }
        }
    }else{
        folding = false;
        bidding = false;
        checking = false;
    }
}

char EventManager::action(){
    if(folding){
        return 'F';
    }else if(checking){
        return 'C';
    }else if(bidding){
        return 'B';
    }

    return 'W';
}