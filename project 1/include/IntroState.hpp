#ifndef INTROSTATE_HPP
#define INTROSTATE_HPP
#include<SFML/Graphics.hpp>
#include "GameState.hpp"

class IntroState: public GameState
{
    public:
        IntroState(Game* game);
        ~IntroState();

        virtual void draw(const float dt);
        virtual void update(const float dt);
        virtual void handleInput();

    private:
        sf::Font mFont;
        sf::Text mIntro;
        void loadmenu();
};

#endif // INTROSTATE_HPP
