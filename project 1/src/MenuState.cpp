#include "MenuState.hpp"
#include "SFML/Graphics.hpp"

#include <iostream>

#include "GameState.hpp"
#include "PlayState.hpp"
#include "CreditState.hpp"
MenuState::MenuState(Game* game)
{
    this->game = game;
    mFont.loadFromFile("arial.ttf");
    mText.setFont(mFont);
    mText.setString(sf::String("MAIN MENU:"));
    mText.setCharacterSize(18);

    sf::FloatRect textRect = mText.getLocalBounds();
    mText.setOrigin(textRect.left + textRect.width/2.0f,
                    textRect.top + textRect.height/2.0f);
    mText.setPosition(400,100);

    mButtonSize = sf::Vector2f(300.0f,32.0f);
    mButtonPos = sf::Vector2f(400,200);
    mButtomPadding =4;
    std::string str[3];
    str[0] = "PLAY";
    str[1] = "CREDIT";
    str[2] = "EXIT";
    for(int i =0;i<3;++i){
        sf::Vector2f buttonPosition(mButtonPos.x,
                                    mButtonPos.y+(i*(mButtonSize.y + mButtomPadding)));
        mRects[i].setSize(mButtonSize);
        mRects[i].setFillColor(sf::Color::White);
        mRects[i].setOrigin(mButtonSize.x/2.0f,mButtonSize.y/2.0f);
        mRects[i].setPosition(buttonPosition);

        mLabel[i].setFont(mFont);
        mLabel[i].setString(sf::String(str[i]));
        mLabel[i].setCharacterSize(12);
        mLabel[i].setColor(sf::Color::Black);

        sf::FloatRect rect = mLabel[i].getLocalBounds();
        mLabel[i].setOrigin(rect.left+rect.width/2.0f,
                            rect.top+rect.height/2.0f);
        mLabel[i].setPosition(buttonPosition);
    }
}
MenuState::~MenuState(){

}
void MenuState::handleInput(){
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
            if (mEvent.key.code == sf::Keyboard::Escape)
                game->window.close();
            break;
        }
    }

}
void MenuState::MouseClick(){
    sf::Vector2i mousePos = sf::Mouse::getPosition(game->window);
	float halfX = mButtonSize.x / 2.0f;
	float halfY = mButtonSize.y / 2.0f;
	for(int i = 0; i < 3; ++i){
		if(mousePos.x >= mRects[i].getPosition().x - halfX &&
			mousePos.x <= mRects[i].getPosition().x + halfX &&
			mousePos.y >= mRects[i].getPosition().y - halfY &&
			mousePos.y <= mRects[i].getPosition().y + halfY &&
            sf::Event::MouseButtonPressed == mEvent.type)
		{
			if(i == 0){
				loadstate(i);
			} else if(i == 1){
				loadstate(i);
			} else if(i == 2){
				game->window.close();
			}
		}
	}
}
void MenuState::update(const float dt){
    MouseClick();
}
void MenuState::draw(const float dt){
    game->window.draw(mText);
    for(int i =0 ;i<3;++i){
        game->window.draw(mRects[i]);
        game->window.draw(mLabel[i]);
    }
}
void MenuState::loadstate(int state){
    switch(state){
        case States::Play:
            game->pushState(new PlayState(game));
            break;
        case States::Credit:
            game->pushState(new CreditState(game));
            break;
    }
}
