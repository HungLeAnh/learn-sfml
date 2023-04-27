#ifndef MAINMENU_HPP
#define MAINMENU_HPP

#include "StateManager.hpp"
#include "LoadState.hpp"
#include "AboutState.hpp"
#include "PlayState.hpp"

#include "Game.hpp"

#include<SFML/Graphics.hpp>
enum State{
    PLAY=0,
    LOAD,
    ABOUT,
    EXIT
};
class MainMenu:public StateManager
{
    public:
        MainMenu(Game* newgame);
        ~MainMenu();

        void Draw(const float dt) override;
        void Update(const float dt) override;
        void HandleInput() override;

    private:
        sf::Font m_font;
        sf::Text m_mainMenu;
        sf::Texture m_textureBackGround;
        sf::Texture m_textureLogo;
        sf::Sprite m_logo;
        sf::Sprite m_backGround;

        sf::Texture m_textureButtonOri;
        sf::Texture m_textureButtonHover;
        sf::Texture m_textureButtonPress;
        sf::Sprite m_Buttons[4];
        sf::Text m_Label[4];

};

#endif // MAINMENU_HPP
