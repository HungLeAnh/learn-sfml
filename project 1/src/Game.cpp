#include "Game.hpp"
//#include "SFML/Graphics.hpp"
#include "GameState.hpp"
Game::Game()
{
    window.create(sf::VideoMode(800, 600), "Project 1");

    window.setFramerateLimit(60);
}
void Game::pushState(GameState* state)
{
    states.push_back(state);

}
void Game::popState()
{
    states.back();
    delete states.back();
    states.pop_back();
}
Game::~Game()
{
    while (!states.empty())
        popState();
}

GameState* Game::CurrentState()
{
    if (states.empty())
        return nullptr;
    else
        return states.back();
}
void Game::gameLoop()
{
    sf::Clock clock;

    while (window.isOpen())
    {
        //control frame rate (you can ignore this stuff for now)
        sf::Time elapsed = clock.restart();
        float dt = elapsed.asSeconds();

        //exception handling
        if (CurrentState() == nullptr)
            continue;

        //get user input for current game state
        CurrentState()->handleInput();

        //update anything neccessary
        CurrentState()->update(dt);

        //clear window
        window.clear();

        //draw anything in the current game state
        CurrentState()->draw(dt);

        window.display();
    }
}
