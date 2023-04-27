#pragma once
#ifndef GAMEPLAY_HPP
#define GAMEPLAY_HPP

#include<array>
#include<memory>
#include<SFML/Graphics.hpp>
#include "Game.hpp"
#include "State.hpp"
#include "Snake.hpp"

class GamePlay: public Engine::State
{
    public:
        GamePlay(std::shared_ptr<Context> &context);
        ~GamePlay();
        void Init() override;
        void ProcessInput() override;
        void Update(sf::Time dt) override;
        void Draw() override;

        void Pause() override;
        void Start() override;
    private:
        std::shared_ptr<Context> m_context;
        sf::Sprite m_grass;
        sf::Sprite m_food;
        std::array<sf::Sprite,4> m_walls;
        Snake m_snake;
        sf::Text m_scoreText;
        int m_score;
        bool m_isPause;

        sf::Vector2f m_snakeDirection;
        sf::Time m_elapsedTime;
};

#endif // GAMEPLAY_HPP
