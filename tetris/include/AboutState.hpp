#ifndef ABOUTSTATE_HPP
#define ABOUTSTATE_HPP

#include "StateManager.hpp"
#include "Game.hpp"

#include<SFML/Graphics.hpp>
class AboutState:public StateManager
{
    public:
        AboutState(Game* newgame);
        ~AboutState();

        void Draw(const float dt) override;
        void Update(const float dt) override;
        void HandleInput() override;
    private:
        sf::Font m_font;
        sf::Text m_about;
        sf::Text m_script;
};

#endif // ABOUTSTATE_HPP
