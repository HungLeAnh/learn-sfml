#pragma once
#ifndef TETROMINO_HPP
#define TETROMINO_HPP
#include <SFML/Graphics.hpp>
#include <time.h>
#include <cstring>

#include "Game.hpp"

const int M = 20;
const int N = 10;

const int X_offset = 10.5;
const int Y_offset = 115;

const float Scale = 0.37;
const int BlockSize = 112;

class Tetromino
{
    struct Point{
        int x;
        int y;
    } a[4],b[4],c[4];
    int figures[7][4]={
        1,3,5,7, // I
        2,4,5,7, // Z
        3,5,4,6, // S
        3,5,4,7, // T
        2,3,5,7, // L
        3,5,7,6, // J
        2,3,4,5, // O
    };
    public:
        Tetromino();
        ~Tetromino();

        int field[M][N] = {0};

        void Reset();
        float GetDelay();
        void SetDelay(float l_delay);
        int GetScore();
        void SetMove(int l_move);
        void IncreaseScore();
        bool HasLost();

        void Lose();
        void ToggleLost();

        void Save(std::string filename);
        void Load(std::string filename);
        void Move();
        void Rotate();
        void CheckLines();
        bool CheckLost();
        bool Check();
        void Tick();
        void Render(sf::RenderWindow& l_window);

    private:
        sf::Texture m_textureTiles;
        sf::Sprite m_tiles;

        int dx=0;
        float m_delay=0.3;
        int colorNum=1;
        int nextcolorNum=1;
        int m_lives;
        int m_score;
        bool m_lost;
        int m_random;
        int m_nextrandom;

};

#endif // TETROMINO_HPP
