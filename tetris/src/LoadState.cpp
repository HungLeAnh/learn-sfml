#include "LoadState.hpp"
#include<iostream>
#include<fstream>
LoadState::LoadState(Game* newgame,Tetromino* l_tetro):m_namePos(0)
{
    this->game = newgame;
    m_tetro=l_tetro;
    m_font.loadFromFile("assets/fonts/telelower.ttf");
    m_load.setFont(m_font);
    m_load.setString(sf::String("LOAD"));
    m_load.setCharacterSize(40);
    m_load.setColor(sf::Color::White);
    sf::FloatRect loadRect = m_load.getLocalBounds();
    m_load.setOrigin(loadRect.left + loadRect.width/2.0f,
                         loadRect.top + loadRect.height/2.0f);
    m_load.setPosition(game->window.getSize().x/2.0f,200.0f);

    //FileName
    std::ifstream loadfile;
    loadfile.open("SavedFile.txt",std::ios::in);
    while(!loadfile.eof()){
        std::string temp;
        std::getline(loadfile,temp);
        m_savedName.push_back(temp);
    }
    for(int i=0;i<m_savedName.size();++i){
        sf::Text temp;
        temp.setCharacterSize(20);
        temp.setFont(m_font);
        temp.setColor(sf::Color::White);
        temp.setString(m_savedName[i]);
        sf::FloatRect nameRect = temp.getLocalBounds();
        temp.setOrigin(nameRect.left + nameRect.width/2.0f,
                                     nameRect.top + nameRect.height/2.0f);
        temp.setPosition(game->window.getSize().x/2.0f, 300.f);
        m_savedNameText.push_back(temp);
    }
    //Button setup
    m_textureButtonOri.loadFromFile("assets/textures/original.png");
    m_textureButtonHover.loadFromFile("assets/textures/hoovered.png");
    m_textureButtonPress.loadFromFile("assets/textures/pressed.png");

    for(int i=0;i<2;++i){
        m_Buttons[i].setTexture(m_textureButtonOri);
        m_Buttons[i].setOrigin(m_Buttons[i].getLocalBounds().left + m_Buttons[i].getLocalBounds().width/2.0f,
                                m_Buttons[i].getLocalBounds().top + m_Buttons[i].getLocalBounds().height/2.0f);
        m_Buttons[i].setPosition(game->window.getSize().x/2.0f,
                                 700.0f +100.0f *i);
    }


    //Label setup
    std::string str[2];
    str[0]="LOAD GAME";
    str[1]="EXIT";
    for(int i=0;i<2;++i){
        m_Label[i].setFont(m_font);
        m_Label[i].setFillColor(sf::Color::Blue);
        m_Label[i].setCharacterSize(20);
        m_Label[i].setString(str[i]);
        sf::FloatRect rect = m_Label[i].getLocalBounds();
        m_Label[i].setOrigin(rect.left+rect.width/2.0f,
                                rect.top+rect.height/2.0f);
        m_Label[i].setPosition(game->window.getSize().x/2.0f,
                            700.0f + 100.0f *i);
    }

}
LoadState::~LoadState(){

}
void LoadState::Draw(const float dt){
    game->window.clear();
    game->window.draw(m_load);
    for(int i=0;i<2;++i){
        game->window.draw(m_Buttons[i]);
        game->window.draw(m_Label[i]);
    }
    game->window.draw(m_savedNameText[m_namePos]);

}
void LoadState::Update(const float dt){

}
void LoadState::HandleInput(){
    sf::Event event;
    sf::Vector2i mousePos = sf::Mouse::getPosition(game->window);
    sf::Vector2f mousePosF(static_cast<float>( mousePos.x ),
                           static_cast<float>( mousePos.y ));
    while(game->window.pollEvent(event)){
        switch(event.type){
        case sf::Event::Closed:
            game->window.close();
            break;
        case sf::Event::KeyPressed:
            if(event.key.code == sf::Keyboard::Escape)
                game->popState();
            if(event.key.code == sf::Keyboard::Up){
                m_namePos--;
                if(m_namePos<0) m_namePos=m_savedNameText.size()-2;
            }
            if(event.key.code == sf::Keyboard::Down){
                m_namePos++;
                if(m_namePos >=m_savedNameText.size()-1) m_namePos=0;
            }
        case sf::Event::MouseMoved:
            for(int i=0;i<2;++i){
                if(m_Buttons[i].getGlobalBounds().contains(mousePosF))
                    m_Buttons[i].setTexture(m_textureButtonHover);
                else
                    m_Buttons[i].setTexture(m_textureButtonOri);
            }
            break;
        case sf::Event::MouseButtonPressed:
            for(int i=0;i<2;++i){
                if(m_Buttons[i].getGlobalBounds().contains(mousePosF)){
                    m_Buttons[i].setTexture(m_textureButtonPress);
                    switch(i){
                    case 0:
                        m_tetro->Load(m_savedName[m_namePos]);
                        game->popState();
                        if(m_Buttons[i].getGlobalBounds().contains(mousePosF))
                            m_Buttons[i].setTexture(m_textureButtonHover);
                        else
                            m_Buttons[i].setTexture(m_textureButtonOri);
                        std::cout<<"Load saved"<<std::endl;
                        break;

                    case 1:
                        game->popState();
                        game->popState();
                        break;
                    }
                }
            }
            break;
        }
    }
}
