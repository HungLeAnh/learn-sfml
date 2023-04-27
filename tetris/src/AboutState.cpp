#include "AboutState.hpp"

AboutState::AboutState(Game* newgame)
{
    this->game = newgame;

    m_font.loadFromFile("assets/fonts/telelower.ttf");
    m_about.setFont(m_font);
    m_about.setCharacterSize(40);
    m_about.setString(sf::String("ABOUT"));
    m_about.setColor(sf::Color::White);
    sf::FloatRect aboutRect = m_about.getLocalBounds();
    m_about.setOrigin(aboutRect.left + aboutRect.width/2.0f,
                         aboutRect.top + aboutRect.height/2.0f);
    m_about.setPosition(game->window.getSize().x/2.0f,100.0f);

    m_script.setFont(m_font);
    m_script.setCharacterSize(20);
    m_script.setColor(sf::Color::White);
    m_script.setString(sf::String("This Tetris game was made by LE ANH HUNG \n All of the resources can be downloaded from my github link"));
    sf::FloatRect scripRect = m_script.getLocalBounds();
    m_script.setOrigin(scripRect.left + scripRect.width/2.0f,
                         scripRect.top + scripRect.height/2.0f);
    m_script.setPosition(game->window.getSize().x/2.0f,200.0f);
}

AboutState::~AboutState()
{
    //dtor
}
void AboutState::Draw(const float dt){
    game->window.clear();
    game->window.draw(m_about);
    game->window.draw(m_script);
}
void AboutState::Update(const float dt){
}
void AboutState::HandleInput(){
    sf::Event event;
    while(game->window.pollEvent(event)){
        switch(event.type){
        case sf::Event::Closed:
            game->window.close();
            break;
        case sf::Event::KeyPressed:
                game->popState();
        }
    }
}
