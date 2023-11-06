#include "event_manager.hpp"

void EventManager::processEvents()
{
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
            case SDLK_d:
                // Miser un dixième
                break;
            case SDLK_q:
                // Se coucher
                break;
            case SDLK_SPACE:
                // Continue la partie sans mise
                break;
            }
            break;
        }
    }
}