#pragma once

#include "level.hpp"
#include "event_manager.hpp"

class UpdateManager
{
public:
    UpdateManager(EventManager &eventManager, Level &level);
    void update();

private:
    EventManager &eventManager;
    Level &level;
};