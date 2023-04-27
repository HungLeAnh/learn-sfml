#include "Tetromino.hpp"
#include<iostream>
#include<fstream>
Tetromino::Tetromino(){
    m_textureTiles.loadFromFile("assets/textures/titles.png");
    m_tiles.setTexture(m_textureTiles);
    srand(time(0));

    m_nextrandom=rand()%7;
    for(int i=0;i<4;i++){
        c[i].x = (figures[m_nextrandom][i] % 2);
        c[i].y = (figures[m_nextrandom][i] / 2);
    }
    nextcolorNum=1+rand()%4;
    m_random=rand()%7;
    for(int i=0;i<4;i++){
        a[i].x = figures[m_random][i] % 2;
        a[i].y = figures[m_random][i] / 2;
    }

    Reset();
}
Tetromino::~Tetromino(){}
float Tetromino::GetDelay(){
    return m_delay;
}
void Tetromino::SetDelay(float l_delay){
    m_delay=l_delay;
}
int Tetromino::GetScore(){
    return m_score;
}
void Tetromino::SetMove(int l_move){
    dx=l_move;
}
void Tetromino::IncreaseScore(){
    m_score +=100;
}
bool Tetromino::HasLost(){
    return m_lost;
}
void Tetromino::Lose(){
    m_lost=true;
}
void Tetromino::ToggleLost(){
    m_lost= !m_lost;
}
void Tetromino::Save(std::string filename){
    std::ofstream file;
    std::string directory = filename+".txt";
    std::cout<<directory<<std::endl;
    file.open(directory);
    file<<m_score<<" "<<colorNum<<" "<<m_random<<std::endl;
    file<<nextcolorNum<<" "<<m_nextrandom<<std::endl;
    for(int i=0;i<4;i++){;
        file<<a[i].x<<" "<<a[i].y<<std::endl;
    }
    for(int i=0;i<M;i++){
        for(int j=0;j<N;j++){
            file<<field[i][j]<<" ";
        }
        file<<std::endl;
    }


}
void Tetromino::Load(std::string filename){
    std::string dir=filename+".txt";
    std::cout<<dir<<std::endl;
    std::ifstream input;
    input.open(dir,std::ios::in);
    input>>m_score>>colorNum>>m_random;
    std::cout<<m_score<<" "<<colorNum<<" "<<m_random<<std::endl;
    input>>nextcolorNum>>m_nextrandom;
    for(int i=0;i<4;i++){
        input>>a[i].x>>a[i].y;
    }
    for(int i=0;i<M;i++){
        for(int j=0;j<N;j++){
            input>>field[i][j];
        }
    }
}
void Tetromino::Reset(){
    for(int i=0;i<M;i++)
        for(int j=0;j<N;j++)
            field[i][j]=0;
    m_score=0;
    m_lost=false;
    dx=0;
    m_delay=0.3;
    colorNum=1;
    std::cout<<"reset"<<std::endl;
}
void Tetromino::Move(){
    for(int i=0;i<4;++i){
        b[i]=a[i];
        a[i].x+=dx;
    }
    if(!Check()){
        for(int i=0;i<4;i++) a[i]=b[i];
    }
}
void Tetromino::Rotate(){
        Point p =a[1];
        for(int i=0;i<4;i++){
            int x = a[i].y -p.y;
            int y = a[i].x -p.x;
            a[i].x = p.x - x;
            a[i].y = p.y + y;
        }
        if(!Check()){
            for(int i=0;i<4;i++) a[i]=b[i];
        }
}
void Tetromino::CheckLines(){
    int k=M-1;
    for(int i=M-1;i>0;i--){
        int icount=0;
        for(int j=0;j<N;j++){
            if(field[i][j]) icount++;
            field[k][j]=field[i][j];
        }
        if(icount<N) k--;
        else if(icount==N) IncreaseScore();
    }
    dx=0; m_delay=0.3;
}
bool Tetromino::Check(){
   for (int i=0;i<4;i++)
      if (a[i].x<0 || a[i].x>=N || a[i].y>=M) return 0;
      else if (field[a[i].y][a[i].x]) return 0;

   return 1;
}
void Tetromino::Tick(){
        for(int i=0;i<4;i++){
            b[i]=a[i];
            a[i].y+=1;
        }

        if (!Check()){
            for (int i=0;i<4;i++) field[b[i].y][b[i].x]=colorNum;

            colorNum=nextcolorNum;
            m_random=m_nextrandom;
            for (int i=0;i<4;i++){
                a[i].x = (figures[m_random][i] % 2);
                a[i].y = (figures[m_random][i] / 2);
               }

            m_nextrandom=rand()%7;
            nextcolorNum=1+rand()%4;
            for(int i=0;i<4;i++){
                c[i].x = (figures[m_nextrandom][i] % 2);
                c[i].y = (figures[m_nextrandom][i] / 2);
            }
        }
        CheckLost();
}
void Tetromino::Render(sf::RenderWindow& l_window){
    if(m_lost){ return; }
    for(int i=0;i<M;i++)
        for(int j=0;j<N;j++){
            if (field[i][j]==0) continue;
            m_tiles.setTextureRect(sf::IntRect(field[i][j]*BlockSize,0,BlockSize,BlockSize));
            m_tiles.setPosition(j*BlockSize*Scale,i*BlockSize*Scale);
            m_tiles.setScale(Scale,Scale);
            m_tiles.move(X_offset,Y_offset); //offset
            l_window.draw(m_tiles);
    }

    for(int i=0;i<4;i++){
        m_tiles.setTextureRect(sf::IntRect(colorNum*BlockSize,0,BlockSize,BlockSize));
        m_tiles.setPosition(a[i].x*BlockSize*Scale,a[i].y*BlockSize*Scale);
        m_tiles.setScale(Scale,Scale);
        m_tiles.move(X_offset,Y_offset); //offset
        l_window.draw(m_tiles);
    }
    for(int i=0;i<4;i++){
        m_tiles.setTextureRect(sf::IntRect(nextcolorNum*BlockSize,0,BlockSize,BlockSize));
        m_tiles.setScale(0.2,0.2);
        m_tiles.setPosition(c[i].x*BlockSize*0.2,c[i].y*BlockSize*0.2);
        m_tiles.move(X_offset+470,Y_offset+75); //offset
        l_window.draw(m_tiles);
    }
}
bool Tetromino::CheckLost(){
    for(int j=0;j<N;j++){
        if(field[1][j]!=0) Lose();
    }
}


