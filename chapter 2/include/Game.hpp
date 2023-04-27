#ifndef GAME_HPP
#define GAME_HPP

#include<Window.hpp>

class Game
{
    public:
        Game();
        ~Game();
        void HandleInput();
        void Update();
        void Render();
        Window* GetWindow();
        sf::Time GetElapsed();
        void RestartClock();

    private:
        void            MoveMushroom();
        Window          mWindow;
        sf::Texture     mMushroomTexture;
        sf::Sprite      mMushroom;
        sf::Vector2u    mIncrement;
        sf::Clock       mClock;
        sf::Time        mElapsed;
};

#endif // GAME_HPP
