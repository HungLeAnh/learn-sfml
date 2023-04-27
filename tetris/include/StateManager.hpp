#pragma once
#ifndef STATE_MANAGER_HPP
#define STATE_MANAGER_HPP
#include "Game.hpp"

class StateManager{
    public:
        Game* game;

        virtual void Draw(const float dt)=0;
        virtual void Update(const float dt)=0;
        virtual void HandleInput()=0;
};

#endif /*STATE_MANAGER*/
