#ifndef GAME_HPP
#define GAME_HPP

#include<list>
#include<SFML/Graphics.hpp>
const float TIME_PER_FRAME = 1.0f/60.0f;

class StateManager;

class Game
{
    public:
        Game();
        ~Game();

        void pushState(StateManager* state);
        void popState();

        StateManager* CurrentState();

        void gameLoop();
        sf::RenderWindow window;
    private:
        std::list<StateManager*> states;
        sf::Time m_elapsed;
        sf::Clock m_clock;
        float m_dt;
};

#endif // GAME_HPP
