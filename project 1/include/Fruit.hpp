#ifndef FRUIT_HPP
#define FRUIT_HPP

#include<SFML/Graphics.hpp>
#include "Snake.hpp"


class Fruit
{
    public:
        Fruit(sf::Vector2u lWindSize);
        ~Fruit();

        int GetBlockSize();

        void RespawnApple();

        void Update(Snake& lPlayer);
        void Render(sf::RenderWindow& lWindow);

    private:
        sf::Vector2u mWindSize;
        sf::Vector2i mItem;
        int mBlockSize;
        sf::CircleShape mApple;
        sf::RectangleShape mBound[4];
};

#endif // FRUIT_HPP
