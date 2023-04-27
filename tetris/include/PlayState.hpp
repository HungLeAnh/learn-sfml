#ifndef PLAYSTATE_HPP
#define PLAYSTATE_HPP

#include "Game.hpp"
#include "StateManager.hpp"
#include "Tetromino.hpp"

#include<string>
#include <time.h>
#include<SFML/Graphics.hpp>
enum Button{
    PAUSE=0,
    SAVE,
    EXIT_PLAY
};
class PlayState: public StateManager
{
    public:
        PlayState(Game* newgame,bool isLoad);
        ~PlayState();

        void Draw(const float dt) override;
        void Update(const float dt) override;
        void HandleInput() override;
    private:
        sf::Font m_font;
        sf::Text m_scoreText;
        sf::Texture m_textureBackGround;
        sf::Sprite m_backGround;

        sf::Texture m_textureButtonOri;
        sf::Texture m_textureButtonHover;
        sf::Texture m_textureButtonPress;
        sf::Sprite m_Buttons[3];
        sf::Text m_Label[3];

        float m_dt;
        bool m_isload;

        Tetromino m_tetro;

};

#endif // PLAYSTATE_HPP
