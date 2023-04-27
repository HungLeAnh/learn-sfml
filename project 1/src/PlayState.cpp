#include "PlayState.hpp"
#include "MenuState.hpp"
#include <iostream>

#include <SFML/Graphics.hpp>

#include "GameState.hpp"



PlayState::PlayState(Game* game):mSnake(mFruit.GetBlockSize()),
mFruit(sf::Vector2u(800,600))
{
    this->game = game;
}
PlayState::~PlayState(){}

void PlayState::draw(const float dt)
{
    mFruit.Render(game->window);
    mSnake.Render(game->window);
}
void PlayState::update(const float dt)
{
    mElapsed +=dt;
    float timestep = 1.0f /mSnake.GetSpeed();
    if(mElapsed >= timestep){
        mSnake.Tick();
        mFruit.Update(mSnake);
        mElapsed -= timestep;
        if(mSnake.HasLost()){
            mSnake.Reset();
        }
    }
}
void PlayState::handleInput()
{
    sf::Event event;

    while (this->game->window.pollEvent(event))
    {
        switch (event.type)
        {
            /* Close the window */
        case sf::Event::Closed:
            this->game->window.close();
            break;
        }
            //pause game
        if (event.type==sf::Event::KeyPressed&&event.key.code == sf::Keyboard::Escape)
            game->pushState(new PauseState(game));
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)
            && mSnake.GetPhysicalDirection() != Direction::Down){
            mSnake.SetDirection(Direction::Up);
        } else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)
            && mSnake.GetPhysicalDirection() != Direction::Up){
            mSnake.SetDirection(Direction::Down);
        } else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)
            && mSnake.GetPhysicalDirection() != Direction::Right){
            mSnake.SetDirection(Direction::Left);
        } else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)
            && mSnake.GetPhysicalDirection() != Direction::Left){
            mSnake.SetDirection(Direction::Right);
        }
    }

}
void PlayState::PauseGame(){

}
