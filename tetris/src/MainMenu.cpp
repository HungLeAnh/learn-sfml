#include "MainMenu.hpp"
#include <iostream>
MainMenu::MainMenu(Game* newgame)
{
    this->game =newgame;
    //Background setup
    m_textureBackGround.loadFromFile("assets/textures/backgroundMenu.png");
    m_textureLogo.loadFromFile("assets/textures/tetris_logo.png");
    m_backGround.setTexture(m_textureBackGround);
    m_logo.setTexture(m_textureLogo);
    m_logo.setOrigin(m_logo.getTextureRect().left+m_logo.getTextureRect().width/2.0f,
                     m_logo.getTextureRect().top+m_logo.getTextureRect().height/2.0f);
    m_logo.setPosition(game->window.getSize().x/2.0f,150.0f);
    m_logo.setScale(0.3f,0.3f);

    //State title setup
    m_font.loadFromFile("assets/fonts/telelower.ttf");
    m_mainMenu.setFont(m_font);
    m_mainMenu.setString(sf::String("MAIN MENU"));
    m_mainMenu.setCharacterSize(40);
    m_mainMenu.setColor(sf::Color::Black);
    sf::FloatRect mainMenuRect = m_mainMenu.getLocalBounds();
    m_mainMenu.setOrigin(mainMenuRect.left + mainMenuRect.width/2.0f,
                         mainMenuRect.top + mainMenuRect.height/2.0f);
    m_mainMenu.setPosition(game->window.getSize().x/2.0f,350.0f);

    //Button setup
    m_textureButtonOri.loadFromFile("assets/textures/original.png");
    m_textureButtonHover.loadFromFile("assets/textures/hoovered.png");
    m_textureButtonPress.loadFromFile("assets/textures/pressed.png");

    for(int i=0;i<4;++i){
        m_Buttons[i].setTexture(m_textureButtonOri);
        m_Buttons[i].setOrigin(m_Buttons[i].getLocalBounds().left + m_Buttons[i].getLocalBounds().width/2.0f,
                               m_Buttons[i].getLocalBounds().top + m_Buttons[i].getLocalBounds().height/2.0f);
        m_Buttons[i].setPosition(game->window.getSize().x/2.0f,
                                 450.0f + 100.0f * i);
    }
    //Label setup
    std::string str[4];
    str[0] = "PLAY";
    str[1] = "LOAD";
    str[2] = "ABOUT";
    str[3] = "EXIT";
    for(int i=0;i<4;++i){
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
MainMenu::~MainMenu(){

}

void MainMenu::Draw(const float dt){
    game->window.clear();
    game->window.draw(m_backGround);
    game->window.draw(m_logo);
    game->window.draw(m_mainMenu);
    for(int i=0;i<4;++i){
        game->window.draw(m_Buttons[i]);
    }
    for(int i=0;i<4;++i){
        game->window.draw(m_Label[i]);
    }
}
void MainMenu::Update(const float dt){
}
void MainMenu::HandleInput(){
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
                game->window.close();
        case sf::Event::MouseMoved:
            for(int i=0;i<4;++i){
                if(m_Buttons[i].getGlobalBounds().contains(mousePosF))
                    m_Buttons[i].setTexture(m_textureButtonHover);
                else
                    m_Buttons[i].setTexture(m_textureButtonOri);
            }
            break;
        case sf::Event::MouseButtonPressed:
            for(int i=0;i<4;++i){
                if(m_Buttons[i].getGlobalBounds().contains(mousePosF)){
                    m_Buttons[i].setTexture(m_textureButtonPress);
                    switch(i){
                    case State::PLAY:
                        game->pushState(new PlayState(game,false));
                        if(m_Buttons[i].getGlobalBounds().contains(mousePosF))
                            m_Buttons[i].setTexture(m_textureButtonHover);
                        else
                            m_Buttons[i].setTexture(m_textureButtonOri);
                        std::cout<<"PLAYSTATE"<<std::endl;
                        break;
                    case State::LOAD:
                        game->pushState(new PlayState(game,true));
                        if(m_Buttons[i].getGlobalBounds().contains(mousePosF))
                            m_Buttons[i].setTexture(m_textureButtonHover);
                        else
                            m_Buttons[i].setTexture(m_textureButtonOri);
                        std::cout<<"LOADSTATE"<<std::endl;
                        break;
                    case State::ABOUT:
                        game->pushState(new AboutState(game));
                        if(m_Buttons[i].getGlobalBounds().contains(mousePosF))
                            m_Buttons[i].setTexture(m_textureButtonHover);
                        else
                            m_Buttons[i].setTexture(m_textureButtonOri);
                        std::cout<<"ABOUTSTATE"<<std::endl;
                        break;
                    case State::EXIT:
                        game->window.close();
                        break;
                    }
                }
            }
            break;
        }
    }
}
