#include "Game.hpp"

Game::Game(): mWindow("",sf::Vector2u(800,600)){
    mMushroomTexture.loadFromFile("Mushroom.png");
    mMushroom.setTexture(mMushroomTexture);
    mIncrement = sf::Vector2u(400,400);
}

Game::~Game()
{
    //dtor
}
Window* Game::GetWindow(){ return &mWindow; }
void Game::HandleInput(){

}
void Game::Update(){
    mWindow.Update();
    MoveMushroom();
}
void Game::MoveMushroom(){
    float fElapsed = mElapsed.asSeconds();

    sf::Vector2u l_windSize = mWindow.GetWindowSize();
    sf::Vector2u l_textSize = mMushroomTexture.getSize();
    if((mMushroom.getPosition().x > l_windSize.x - l_textSize.x && mIncrement.x>0)||
       (mMushroom.getPosition().x < 0 && mIncrement.x<0)){
        mIncrement.x=-mIncrement.x;
    }
    if((mMushroom.getPosition().y > l_windSize.y - l_textSize.y && mIncrement.y>0)||
       (mMushroom.getPosition().y < 0 && mIncrement.y<0)){
        mIncrement.y=-mIncrement.y;
    }
    mMushroom.setPosition(mMushroom.getPosition().x + (mIncrement.x * fElapsed),
                          mMushroom.getPosition().y + (mIncrement.y * fElapsed));
}
void Game::Render(){
    mWindow.BeginDraw();
    mWindow.Draw(mMushroom);
    mWindow.EndDraw();
}
sf::Time Game::GetElapsed(){  return mElapsed;  }
void Game::RestartClock(){

    mElapsed += mClock.restart();
    float frametime= 1.0f/60.0f;
    if(mElapsed.asSeconds() >= frametime){
        mElapsed-=sf::seconds(frametime);
    }
}
