#ifndef PAUSESTATE_HPP
#define PAUSESTATE_HPP

#include "Game.hpp"
#include "StateManager.hpp"

#include<SFML/Graphics.hpp>
class PauseState:public StateManager
{
    public:
        PauseState(Game* newgame);
        ~PauseState();

        void Draw(const float dt) override;
        void Update(const float dt) override;
        void HandleInput() override;
    private:
        sf::Font m_font;
        sf::Text m_pause;
        sf::RectangleShape m_backGroundShape;

        sf::Texture m_textureButtonOri;
        sf::Texture m_textureButtonHover;
        sf::Texture m_textureButtonPress;
        sf::Sprite m_Buttons[2];
        sf::Text m_Label[2];
};

#endif // PAUSESTATE_HPP
