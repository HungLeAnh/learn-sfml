#include "SplashState.hpp"
#include "MainMenu.hpp"
SplashState::SplashState(Game* newgame):m_isSplashShown(false)
{
    this->game = newgame;
    m_font.loadFromFile("assets/fonts/arial.ttf");
    m_splash.setFont(m_font);
    m_splash.setCharacterSize(15);
    m_splash.setString(sf::String("PRESS ANYKEY TO CONTINUE"));
    m_splash.setColor(sf::Color::White);
    sf::FloatRect textRect = m_splash.getLocalBounds();
    m_splash.setPosition(game->window.getSize().x/2,game->window.getSize().y*3.0f/4.0f);
    m_splash.setOrigin(textRect.left + textRect.width/2.0f,
                       textRect.top + textRect.height/2.0f);

    m_texture.loadFromFile("assets/textures/tetris_logo.png");
    m_logo.setTexture(m_texture);
    m_logo.setPosition(game->window.getSize().x/2,game->window.getSize().y/3);
    sf::FloatRect logoRect = m_logo.getLocalBounds();
    m_logo.setOrigin(logoRect.left + logoRect.width/2.0f,
                     logoRect.top + logoRect.height/2.0f);
    m_logo.setScale(0.3f,0.3f);

}

SplashState::~SplashState()
{

}
void SplashState::HandleInput(){
    sf::Event event;
    while(game->window.pollEvent(event)){
        switch(event.type){
        case sf::Event::Closed:
            game->window.close();
            break;
        case sf::Event::KeyPressed:
            if(event.key.code == sf::Keyboard::Escape)
                game->window.close();
            else
                LoadNextState();
        }
    }
}
void SplashState::Update(const float dt){
    const float BLINK_TIME = 0.8f;
    m_dt +=dt;
    if(m_dt>=BLINK_TIME){
        m_isSplashShown =! m_isSplashShown;
        m_dt -= BLINK_TIME;

    }
}
void SplashState::Draw(const float dt){
    game->window.clear();
    game->window.draw(m_logo);
    if(m_isSplashShown)
        game->window.draw(m_splash);
}
void SplashState::LoadNextState(){
    game->pushState(new MainMenu(game));
}
