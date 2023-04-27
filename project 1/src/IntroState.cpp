#include "IntroState.hpp"
#include "GameState.hpp"
#include "MenuState.hpp"
#include "Game.hpp"
#include<SFML/Graphics.hpp>

#include<iostream>

IntroState::IntroState(Game* game)
{
    this->game = game;
    mFont.loadFromFile("arial.ttf");
    mIntro.setFont(mFont);
    mIntro.setCharacterSize(16);
    mIntro.setString({"\t\tIntro\nMy SNAKE GAME\nPRESS TO START"});
    mIntro.setColor(sf::Color::White);
    sf::FloatRect textRect = mIntro.getLocalBounds();
    mIntro.setPosition(game->window.getSize().x/2,game->window.getSize().y/2);
    mIntro.setOrigin(textRect.left + textRect.width / 2.0f,
		textRect.top + textRect.height / 2.0f);
}

IntroState::~IntroState()
{

}
void IntroState::handleInput(){
    sf::Event event;
    while (game->window.pollEvent(event))
    {
        switch (event.type)
        {
            /* Close the window */
        case sf::Event::Closed:
            game->window.close();
            break;
            /* Change Between game states */
        case sf::Event::KeyPressed:
            if (event.key.code == sf::Keyboard::Escape)
                game->window.close();
            else
                loadmenu();
       break;
        }
    }
}
void IntroState::update(const float dt){}
void IntroState::draw(const float dt){
    game->window.draw(mIntro);
}
void IntroState::loadmenu(){
    game->pushState(new MenuState(game));
}
