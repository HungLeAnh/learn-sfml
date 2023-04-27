#include "CreditState.hpp"
#include "SFML/Graphics.hpp"

#include<iostream>

#include "GameState.hpp"
#include "MenuState.hpp"
CreditState::CreditState(Game* game)
{
    //ctor
    this->game = game;
    mFont.loadFromFile("arial.ttf");
    mText.setFont(mFont);
    mText.setString(sf::String("CREDIT\nMade by LEANHHUNG\nGithub link: https://github.com/Hunglee-wjbu/learn-sfml/tree/main/project%201\nPress esc to exit"));
    mText.setCharacterSize(18);

    sf::FloatRect textRect = mText.getLocalBounds();
    mText.setOrigin(textRect.left +textRect.width/2.0f,
                    textRect.top  +textRect.height/2.0f);
    mText.setPosition(400,100);

    mButtonSize = sf::Vector2f(300.0f,32.0f);
    mButtonPos = sf::Vector2f(400,200);
    mButtomPadding = 4;

}
CreditState::~CreditState()
{
    //dtor
}
void CreditState::draw(const float dt){
    game->window.draw(mText);
}
void CreditState::update(const float dt){

}
void CreditState::handleInput(){
    while (game->window.pollEvent(mEvent))
    {
        switch (mEvent.type)
        {
            /* Close the window */
        case sf::Event::Closed:
            game->window.close();
            break;
            /* Change Between game states */
        case sf::Event::KeyPressed:
            game->popState();
            break;
        }
    }
}
