#ifndef PAUSEGAME_HPP
#define PAUSEGAME_HPP

#include<memory>
#include<SFML/Graphics.hpp>
#include<SFML/Window.hpp>
#include "State.hpp"
#include "Game.hpp"
#include "GamePlay.hpp"

class PauseGame:public Engine::State
{
    public:
        PauseGame(std::shared_ptr<Context> &context);
        virtual ~PauseGame();
        void Init() override;
        void ProcessInput() override;
        void Update(sf::Time dt) override;
        void Draw() override;

    private:
        std::shared_ptr<Context> m_context;
        sf::Text m_pauseTitle;
};

#endif // PAUSEGAME_HPP
