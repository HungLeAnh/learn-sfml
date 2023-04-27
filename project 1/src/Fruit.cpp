#include "Fruit.hpp"

Fruit::Fruit(sf::Vector2u lWindSize)
{
    mBlockSize=16;
    mWindSize = lWindSize;
    RespawnApple();
    mApple.setFillColor(sf::Color::Red);
    mApple.setRadius(mBlockSize/2);

    for(int i=0;i<4;++i){
        mBound[i].setFillColor(sf::Color(150,0,0));
        if(!((i+1)%2)){
            mBound[i].setSize(sf::Vector2f(mWindSize.x,mBlockSize));
        }
        else{
            mBound[i].setSize(sf::Vector2f(mBlockSize,mWindSize.y));
        }
        if(i<2){
            mBound[i].setPosition(0,0);
        }
        else{
            mBound[i].setOrigin(mBound[i].getSize());
            mBound[i].setPosition(sf::Vector2f(mWindSize));
        }
    }
}
Fruit::~Fruit()
{
    //dtor
}
int Fruit::GetBlockSize(){
    return mBlockSize;
}
void Fruit::RespawnApple(){
    int maxX=(mWindSize.x/mBlockSize)-2;
    int maxY=(mWindSize.y/mBlockSize)-2;
    mItem = sf::Vector2i(rand()% maxX+1,rand()% maxY+1);
    mApple.setPosition(mItem.x * mBlockSize,mItem.y * mBlockSize);
}
void Fruit::Update(Snake& lPlayer){
    if(lPlayer.GetPosition() == mItem){
        lPlayer.Extend();
        lPlayer.IncreaseScore();
        RespawnApple();
    }
    int gridSizeX = mWindSize.x/mBlockSize;
    int gridSizeY = mWindSize.y/mBlockSize;

    if(lPlayer.GetPosition().x<=0 ||
       lPlayer.GetPosition().y<=0 ||
       lPlayer.GetPosition().x>=gridSizeX -1 ||
       lPlayer.GetPosition().y>=gridSizeY -1 ){
        lPlayer.Lose();
       }
}
void Fruit::Render(sf::RenderWindow& lWindow){
    for(int i=0;i<4;++i){
        lWindow.draw(mBound[i]);
    }
    lWindow.draw(mApple);
}
