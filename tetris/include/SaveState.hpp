#ifndef SAVESTATE_HPP
#define SAVESTATE_HPP

#include "Game.hpp"
#include "StateManager.hpp"
#include "Tetromino.hpp"

#include<SFML/Graphics.hpp>
class SaveState:public StateManager
{
    public:
        SaveState(Game* newgame,Tetromino l_tetro);
        ~SaveState();

        void Draw(const float dt)override;
        void Update(const float dt)override;
        void HandleInput()override;
    private:
        sf::Font m_font;
        sf::Text m_save;
        sf::Text m_name;
        sf::Text your_name;
        std::string s_str;

        sf::Texture m_textureButtonOri;
        sf::Texture m_textureButtonHover;
        sf::Texture m_textureButtonPress;
        sf::Sprite m_Buttons[2];
        sf::Text m_Label[2];
        Tetromino m_tetro;

};

#endif // SAVESTATE_HPP
