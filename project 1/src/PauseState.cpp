#include "PauseState.hpp"

PauseState::PauseState(Game* game){
    this->game = game;
    mFont.loadFromFile("arial.ttf");
    mText.setString(sf::String("PAUSE"));
    mText.setCharacterSize(18);

    sf::FloatRect textRect = mText.getLocalBounds();
    mText.setOrigin(textRect.left + textRect.width/2.0f,
                    textRect.top + textRect.height/2.0f);
    mText.setPosition(400,100);

    mButtonSize = sf::Vector2f(300.0f,32.0f);
    mButtonPos = sf::Vector2f(400,200);
    mButtomPadding =4;
    std::string str[2];
    str[0]="RESUME";
    str[1]="EXIT";
    for(int i=0;i<2;++i){
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
PauseState::~PauseState()
{

}
void PauseState::handleInput(){
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
                game->popState();

            break;
        }
    }
}
void PauseState::MouseClick(){
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
				game->popState();
			} else if(i == 1){
				game->pushState(new MenuState(game));
			}
		}
	}
}
void PauseState::update(const float dt){
    MouseClick();
}
void PauseState::draw(const float dt){
    game->window.draw(mText);
    for(int i=0;i<2;++i){
        game->window.draw(mRects[i]);
        game->window.draw(mLabel[i]);
    }
}
