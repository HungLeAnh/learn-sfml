#ifndef GAMEOVERSTATE_HPP
#define GAMEOVERSTATE_HPP

#include "Game.hpp"
#include "StateManager.hpp"

#include<SFML/Graphics.hpp>
class GameOverState:public StateManager
{
    public:
        GameOverState(Game* newgame);
        ~GameOverState();
        void Draw(const float dt) override;
        void Update(const float dt) override;
        void HandleInput() override;
    private:
        sf::Font m_font;
        sf::Text m_gameOver;
        sf::RectangleShape m_backGroundShape;
        sf::Texture m_textureButtonOri;
        sf::Texture m_textureButtonHover;
        sf::Texture m_textureButtonPress;
        sf::Sprite m_Buttons[2];
        sf::Text m_Label[2];
};

#endif // GAMEOVERSTATE_HPP
