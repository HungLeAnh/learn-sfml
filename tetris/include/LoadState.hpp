#ifndef LOADSTATE_HPP
#define LOADSTATE_HPP

#include "Game.hpp"
#include "StateManager.hpp"
#include "Tetromino.hpp"

#include<SFML/Graphics.hpp>
#include<vector>

class LoadState:public StateManager
{
    public:
        LoadState(Game* newgame,Tetromino* l_tetro);
        ~LoadState();

        void Draw(const float dt)override;
        void Update(const float dt)override ;
        void HandleInput() override;

    private:
        sf::Font m_font;
        sf::Text m_load;
        sf::Text m_name;
        sf::Text your_name;
        std::string s_str;
        std::vector<std::string> m_savedName;
        std::vector<sf::Text> m_savedNameText;
        int m_namePos;

        sf::Texture m_textureButtonOri;
        sf::Texture m_textureButtonHover;
        sf::Texture m_textureButtonPress;
        sf::Sprite m_Buttons[2];
        sf::Text m_Label[2];
        Tetromino* m_tetro;
};

#endif // LOADSTATE_HPP
