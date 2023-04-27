#ifndef SPLASHSTATE_HPP
#define SPLASHSTATE_HPP

#include "StateManager.hpp"
#include "Game.hpp"

#include<SFML/Graphics.hpp>

class SplashState:public StateManager
{
    public:
        SplashState(Game* newgame);
        ~SplashState();

        void Draw(const float dt) override;
        void Update(const float dt) override;
        void HandleInput() override;

    private:
        sf::Font m_font;
        sf::Text m_splash;
        sf::Texture m_texture;
        sf::Sprite m_logo;
        float m_dt;
        bool m_isSplashShown;

        void LoadNextState();
};

#endif // SPLASHSTATE_HPP
