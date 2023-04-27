#include "Snake.hpp"

Snake::Snake(int lBlockSize)
{
    mSize=lBlockSize;
    mBodyRect.setSize(sf::Vector2f(mSize-1,mSize-1));
    Reset();
}

Snake::~Snake(){}

void Snake::SetDirection(Direction lDir){
    mDir=lDir;
}
Direction Snake::GetDirection(){
    return mDir;
}
int Snake::GetSpeed(){
    return mSpeed;
}
sf::Vector2i Snake::GetPosition(){
    return (!mSnakeBody.empty()? mSnakeBody.front().position : sf::Vector2i(1,1));
}
int Snake::GetLives(){
    return mLives;
}
int Snake::GetScore(){
    return mScore;
}
void Snake::IncreaseScore(){
    mScore +=1;

}
bool Snake::HasLost(){
    return mLost;
}
void Snake::Lose(){
    mLost=true;
}
void Snake::ToggleLost(){
    mLost= !mLost;
}
Direction Snake::GetPhysicalDirection(){
    if(mSnakeBody.size()<=1){
        return Direction::None;
    }

    SnakeSegment& head = mSnakeBody[0];
    SnakeSegment& neck = mSnakeBody[1];
    if(head.position.x ==neck.position.x){
        return (head.position.y >neck.position.y ?
                Direction::Down : Direction::Up);
    }
    else if(head.position.y == neck.position.y){
        return (head.position.x > neck.position.x ?
                Direction::Right : Direction::Left);
    }

    return Direction::None;
}
void Snake::Extend(){
    if(mSnakeBody.empty()){ return; }
    SnakeSegment& tail_head= mSnakeBody[mSnakeBody.size()-1];

    if(mSnakeBody.size()>1){
        SnakeSegment& tail_bone=mSnakeBody[mSnakeBody.size()-2];

        if(tail_head.position.x == tail_bone.position.x){
            (tail_head.position.y>tail_bone.position.y)?
            mSnakeBody.push_back(SnakeSegment(tail_head.position.x,tail_head.position.y+1)):
            mSnakeBody.push_back(SnakeSegment(tail_head.position.x,tail_head.position.y-1));
        }
        else if(tail_head.position.y == tail_bone.position.y){
            (tail_head.position.x>tail_bone.position.y)?
            mSnakeBody.push_back(SnakeSegment(tail_head.position.x+1,tail_head.position.y)):
            mSnakeBody.push_back(SnakeSegment(tail_head.position.x-1,tail_head.position.y));
        }
    }
    else{
        switch(mDir){
        case Direction::Up:
            mSnakeBody.push_back(SnakeSegment(tail_head.position.x,tail_head.position.y+1));
            break;
        case Direction::Down:
            mSnakeBody.push_back(SnakeSegment(tail_head.position.x,tail_head.position.y-1));
            break;
        case Direction::Left:
            mSnakeBody.push_back(SnakeSegment(tail_head.position.x+1,tail_head.position.y));
            break;
        case Direction::Right:
            mSnakeBody.push_back(SnakeSegment(tail_head.position.x-1,tail_head.position.y+1));
            break;
        }
    }
}
void Snake::Reset(){
    mSnakeBody.clear();
    mSnakeBody.push_back(SnakeSegment(5,7));
    mSnakeBody.push_back(SnakeSegment(5,6));
    mSnakeBody.push_back(SnakeSegment(5,5));

    SetDirection(Direction::None);
    mSpeed=6;
    mLives=3;
    mScore=0;
    mLost=false;
}
void Snake::CheckCollision(){
    if(mSnakeBody.size()<5){return;}
    SnakeSegment& head = mSnakeBody.front();
    for(auto itr = mSnakeBody.begin()+1;itr!=mSnakeBody.end();++itr){
        if(itr->position == head.position){
            int segments = mSnakeBody.end()-itr;
            Cut(segments);
            break;
        }
    }
}void Snake::Move(){
    for(int i = mSnakeBody.size()-1;i>0;--i){
        mSnakeBody[i].position = mSnakeBody[i-1].position;
    }
    switch(mDir){
        case Direction::Up:
            --mSnakeBody[0].position.y;
            break;
        case Direction::Down:
            ++mSnakeBody[0].position.y;
            break;
        case Direction::Left:
            --mSnakeBody[0].position.x;
            break;
        case Direction::Right:
            ++mSnakeBody[0].position.x;
            break;
    }
}
void Snake::Tick(){
    if(mSnakeBody.empty()){return;}
    if(mDir == Direction::None){return;}
    Move();
    CheckCollision();
}
void Snake::Cut(int segments){
    for(int i=0;i<segments;++i){
        mSnakeBody.pop_back();
    }
    --mLives;
    if(!mLives){
        Lose();
        return;
    }

}
void Snake::Render(sf::RenderWindow& lWindow){
    if(mSnakeBody.empty()){return;}
    auto head = mSnakeBody.begin();
    mBodyRect.setFillColor(sf::Color::Yellow);
    mBodyRect.setPosition(head->position.x*mSize,head->position.y*mSize);
    lWindow.draw(mBodyRect);

    mBodyRect.setFillColor(sf::Color::Green);
    for(auto itr = mSnakeBody.begin()+1;itr!=mSnakeBody.end();++itr){
        mBodyRect.setPosition(itr->position.x*mSize,itr->position.y*mSize);
        lWindow.draw(mBodyRect);
    }
}
