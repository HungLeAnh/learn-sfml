#include "Game.hpp"

#include "StateManager.hpp"
#include<iostream>

Game::Game(): m_dt(0),m_elapsed(sf::Time::Zero),m_clock()
{
    window.create(sf::VideoMode(590,960),"Tetris 1");
    window.setFramerateLimit(60);
}
Game::~Game()
{
    while(!states.empty()){
        popState();
    }
}
void Game::popState(){
//    states.back();
//    delete states.back();
    states.pop_back();
}
void Game::pushState(StateManager* state){
    states.push_back(state);
}
StateManager* Game::CurrentState(){
    if(states.empty()){
        return nullptr;
    }
    else
        return states.back();
}
void Game::gameLoop(){
    while(window.isOpen()){
        m_elapsed = m_clock.restart();
        m_dt = m_elapsed.asSeconds();
        if(CurrentState() == nullptr)
                continue;

            CurrentState()->HandleInput();

            CurrentState()->Update(m_dt);

            CurrentState()->Draw(m_dt);

            window.display();

    }
}
