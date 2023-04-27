#ifndef PAUSESTATE_HPP
#define PAUSESTATE_HPP

#include<SFML/Graphics.hpp>

#include "GameState.hpp"
#include "MenuState.hpp"


class PauseState: public GameState
{
    public:
        PauseState(Game* game);
        ~PauseState();
        virtual void draw(const float dt);
        virtual void update(const float dt);
        virtual void handleInput();
        void MouseClick();
    private:
        sf::Font mFont;
        sf::Text mText;

        sf::Vector2f mButtonSize;
        sf::Vector2f mButtonPos;
        unsigned int mButtomPadding;

        sf::RectangleShape mRects[3];
        sf::Text mLabel[3];
        sf::Event mEvent;
};

#endif // PAUSESTATE_HPP
