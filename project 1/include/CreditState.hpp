#ifndef CREDITSTATE_HPP
#define CREDITSTATE_HPP

#include<SFML/Graphics.hpp>

#include "GameState.hpp"

class CreditState : public GameState
{
    public:
        CreditState(Game* game);
        ~CreditState();
        virtual void draw(const float dt);
        virtual void update(const float dt);
        virtual void handleInput();

    private:
        sf::Font mFont;
        sf::Text mText;

        sf::Vector2f mButtonSize;
        sf::Vector2f mButtonPos;
        unsigned int mButtomPadding;

        sf::Event mEvent;

};

#endif // CREDITSTATE_HPP
