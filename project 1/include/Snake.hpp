#ifndef SNAKE_HPP
#define SNAKE_HPP

#include<SFML/Graphics.hpp>
#include<vector>

struct SnakeSegment{
    SnakeSegment(int x,int y): position(x,y){}
    sf::Vector2i position;
};

using SnakeContainer = std::vector<SnakeSegment>;
enum class Direction{ None,Up,Down,Left,Right};

class Snake
{
    public:
        Snake(int lBlockSize);
        ~Snake();

        void SetDirection(Direction lDir);
        Direction GetDirection();
        int GetSpeed();
        sf::Vector2i GetPosition();
        int GetLives();
        int GetScore();
        void IncreaseScore();
        bool HasLost();

        void Lose();
        void ToggleLost();

        Direction GetPhysicalDirection();

        void Extend();
        void Reset();

        void Move();
        void Tick();
        void Cut(int lSegments);
        void Render(sf::RenderWindow& lWindow);

    private:
        void CheckCollision();
        SnakeContainer mSnakeBody;
        int mSize;
        Direction mDir;
        int mSpeed;
        int mLives;
        int mScore;
        bool mLost;
        sf::RectangleShape mBodyRect;

};

#endif // SNAKE_HPP
