#include "PlayState.hpp"
#include "PauseState.hpp"
#include "LoadState.hpp"
#include "GameOverState.hpp"
#include "SaveState.hpp"
#include<iostream>
PlayState::PlayState(Game* newgame,bool isLoad):m_tetro(),m_dt(0)
{

    this->game =newgame;
    m_isload = isLoad;

    //Background setup
    m_textureBackGround.loadFromFile("assets/textures/background.jpg");
    m_textureBackGround.setSmooth(true);
    m_backGround.setTexture(m_textureBackGround);
    //m_backGround.scale((game->window.getSize().x/m_backGround.getLocalBounds().width),
    //                   (game->window.getSize().y/m_backGround.getLocalBounds().height));
    //
    m_font.loadFromFile("assets/fonts/telelower.ttf");
    m_scoreText.setFont(m_font);
    m_scoreText.setCharacterSize(18);
    m_scoreText.setString(sf::String(std::to_string(m_tetro.GetScore())));
    sf::FloatRect scoreRect = m_scoreText.getLocalBounds();
    m_scoreText.setOrigin(scoreRect.left + scoreRect.width/2.0f,
                          scoreRect.top + scoreRect.height/2.0f);
    m_scoreText.setPosition(game->window.getSize().x * 13/14.0f,114.0f);
    //Button setup
    m_textureButtonOri.loadFromFile("assets/textures/original.png");
    m_textureButtonHover.loadFromFile("assets/textures/hoovered.png");
    m_textureButtonPress.loadFromFile("assets/textures/pressed.png");
    for(int i=0;i<3;++i){
        m_Buttons[i].setTexture(m_textureButtonOri);
        m_Buttons[i].setOrigin(m_Buttons[i].getLocalBounds().left + m_Buttons[i].getLocalBounds().width/2.0f,
                               m_Buttons[i].getLocalBounds().top + m_Buttons[i].getLocalBounds().height/2.0f);
        m_Buttons[i].setScale(0.8f,0.5f);
        m_Buttons[i].setPosition(game->window.getSize().x * 9.5f/11.0f,400+50.0f * i);
    }
    //Label setup
    std::string str[3];
    str[0] = "PAUSE";
    str[1] = "SAVE";
    str[2] = "EXIT";
    for(int i=0;i<3;++i){
        m_Label[i].setFont(m_font);
        m_Label[i].setFillColor(sf::Color::Blue);
        m_Label[i].setCharacterSize(18);
        m_Label[i].setString(str[i]);
        sf::FloatRect rect = m_Label[i].getLocalBounds();
        m_Label[i].setOrigin(rect.left+rect.width/2.0f,
                             rect.top+rect.height/2.0f);
        m_Label[i].setPosition(game->window.getSize().x* 9.5f/11.0f,400+50.0f *i);
    }
}
PlayState::~PlayState()
{
    //dtor
}
void PlayState::Draw(const float dt){
    game->window.clear();
    game->window.draw(m_backGround);
    game->window.draw(m_scoreText);
    for(int i=0;i<3;++i){
        game->window.draw(m_Buttons[i]);
    }
    for(int i=0;i<3;++i){
        game->window.draw(m_Label[i]);
    }
    m_tetro.Render(game->window);
}
void PlayState::Update(const float dt){
    m_dt +=dt;
    float timestep =m_tetro.GetDelay();
    if(m_dt >= timestep){
        m_tetro.Tick();
        m_tetro.CheckLines();
        m_scoreText.setString(sf::String(std::to_string(m_tetro.GetScore())));
        m_dt-=timestep;
        if(m_tetro.HasLost()){
            m_tetro.Reset();
            game->pushState(new GameOverState(game));
            std::cout<<"lose"<<std::endl;
        }
    }
//std::cout<<m_dt<<std::endl;
}
void PlayState::HandleInput(){
    if(m_isload){
        std::cout<<"isload"<<std::endl;
        game->pushState(new LoadState(game,&m_tetro));
        m_isload = !m_isload;
    }
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
                if(event.key.code == sf::Keyboard::Escape){
                    game->pushState(new PauseState(game));
                }
                if (event.key.code==sf::Keyboard::Up) m_tetro.Rotate();
                else if(event.key.code==sf::Keyboard::Left){
                    m_tetro.SetMove(-1);
                    m_tetro.Move();
                }
                else if(event.key.code==sf::Keyboard::Right){
                    m_tetro.SetMove(1);
                    m_tetro.Move();
                }
                break;
            case sf::Event::MouseMoved:
                for(int i=0;i<3;++i){
                    if(m_Buttons[i].getGlobalBounds().contains(mousePosF))
                        m_Buttons[i].setTexture(m_textureButtonHover);
                    else
                        m_Buttons[i].setTexture(m_textureButtonOri);
                }
                break;
            case sf::Event::MouseButtonPressed:
                for(int i=0;i<3;++i){
                    if(m_Buttons[i].getGlobalBounds().contains(mousePosF)){
                        m_Buttons[i].setTexture(m_textureButtonPress);
                        switch(i){
                        case Button::PAUSE:
                            game->pushState(new PauseState(game));
                            if(m_Buttons[i].getGlobalBounds().contains(mousePosF))
                                m_Buttons[i].setTexture(m_textureButtonHover);
                            else
                                m_Buttons[i].setTexture(m_textureButtonOri);
                            std::cout<<"PAUSE"<<std::endl;
                            break;
                        case Button::SAVE:
                            game->pushState(new SaveState(game,m_tetro));
                            if(m_Buttons[i].getGlobalBounds().contains(mousePosF))
                                m_Buttons[i].setTexture(m_textureButtonHover);
                            else
                                m_Buttons[i].setTexture(m_textureButtonOri);
                            break;
                        case Button::EXIT_PLAY:
                            game->popState();
                            break;
                        }
                    }
                }
                break;
            }
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) m_tetro.SetDelay(0.05);
    else m_tetro.SetDelay(0.3);
}
