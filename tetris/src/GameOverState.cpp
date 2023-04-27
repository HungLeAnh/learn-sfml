#include "GameOverState.hpp"
#include<iostream>
GameOverState::GameOverState(Game* newgame)
{
    this->game= newgame;

    m_font.loadFromFile("assets/fonts/telelower.ttf");
    m_gameOver.setFont(m_font);
    m_gameOver.setString(sf::String("!!!GAME OVER!!!"));
    m_gameOver.setCharacterSize(40);
    m_gameOver.setColor(sf::Color::White);
    sf::FloatRect pauseRect = m_gameOver.getLocalBounds();
    m_gameOver.setOrigin(pauseRect.left + pauseRect.width/2.0f,
                         pauseRect.top + pauseRect.height/2.0f);
    m_gameOver.setPosition(game->window.getSize().x/2.0f,350.0f);

    //Background setup
    m_backGroundShape.setFillColor(sf::Color(0,0,0,100));
    m_backGroundShape.setSize(sf::Vector2f(game->window.getSize().x,game->window.getSize().y));
    game->window.draw(m_backGroundShape);

    //Button setup
    m_textureButtonOri.loadFromFile("assets/textures/original.png");
    m_textureButtonHover.loadFromFile("assets/textures/hoovered.png");
    m_textureButtonPress.loadFromFile("assets/textures/pressed.png");

    for(int i=0;i<2;++i){
        m_Buttons[i].setTexture(m_textureButtonOri);
        m_Buttons[i].setOrigin(m_Buttons[i].getLocalBounds().left + m_Buttons[i].getLocalBounds().width/2.0f,
                               m_Buttons[i].getLocalBounds().top + m_Buttons[i].getLocalBounds().height/2.0f);
        m_Buttons[i].setPosition(game->window.getSize().x/2.0f,
                                 450.0f + 100.0f * i);
    }
    //Label setup
    std::string str[2];
    str[0] = "REPLAY";
    str[1] = "EXIT";
    for(int i=0;i<2;++i){
        m_Label[i].setFont(m_font);
        m_Label[i].setFillColor(sf::Color::Blue);
        m_Label[i].setCharacterSize(18);
        m_Label[i].setString(str[i]);
        sf::FloatRect rect = m_Label[i].getLocalBounds();
        m_Label[i].setOrigin(rect.left+rect.width/2.0f,
                             rect.top+rect.height/2.0f);
        m_Label[i].setPosition(game->window.getSize().x/2.0f,
                            450.0f + 100.0f *i);
    }
}

GameOverState::~GameOverState()
{
    //dtor
}
void GameOverState::Draw(const float dt){
    game->window.draw(m_gameOver);
    for(int i=0;i<2;++i){
        game->window.draw(m_Buttons[i]);
    }
    for(int i=0;i<2;++i){
        game->window.draw(m_Label[i]);
    }
}
void GameOverState::Update(const float dt){

}
void GameOverState::HandleInput(){
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
                        game->popState();
                        if(m_Buttons[i].getGlobalBounds().contains(mousePosF))
                            m_Buttons[i].setTexture(m_textureButtonHover);
                        else
                            m_Buttons[i].setTexture(m_textureButtonOri);
                        std::cout<<"PLAYSTATE"<<std::endl;
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
