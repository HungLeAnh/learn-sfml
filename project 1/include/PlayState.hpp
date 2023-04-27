#pragma once
#ifndef GAME_STATE_EDITOR_HPP
#define GAME_STATE_EDITOR_HPP

#include <SFML/Graphics.hpp>

#include "GameState.hpp"
#include "PauseState.hpp"
#include "Fruit.hpp"
#include "Snake.hpp"


class PlayState : public GameState
{
public:
    PlayState(Game* game);
    ~PlayState();

    virtual void draw(const float dt);
    virtual void update(const float dt);
    virtual void handleInput();

private:
    float mElapsed;
    Fruit mFruit;
    Snake mSnake;
    void PauseGame();
    void loadstate();
};

#endif /* GAME_STATE_EDITOR_HPP */
