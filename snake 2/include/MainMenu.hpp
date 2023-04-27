#ifndef MAINMENU_HPP
#define MAINMENU_HPP

#include<memory>
#include<SFML/Graphics.hpp>
#include<SFML/Window.hpp>
#include "State.hpp"
#include "Game.hpp"
#include "GamePlay.hpp"


class MainMenu: public Engine::State
{
    public:
        MainMenu(std::shared_ptr<Context>& context);
        ~MainMenu();

        void Init() override;
        void ProcessInput() override;
        void Update(sf::Time dt) override;
        void Draw() override;

    protected:

    private:
        std::shared_ptr<Context> m_context;
        sf::Text m_gameTitle;
        sf::Text m_playButton;
        sf::Text m_exitButton;

        bool m_isPlayButtonSelected;
        bool m_isPlayButtonPressed;
        bool m_isExitButtonSelected;
        bool m_isExitButtonPressed;
};

#endif // MAINMENU_HPP
