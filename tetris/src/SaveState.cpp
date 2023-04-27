#include "SaveState.hpp"
#include<fstream>
SaveState::SaveState(Game* newgame,Tetromino l_tetro)
{
    this->game= newgame;

    m_tetro=l_tetro;

    m_font.loadFromFile("assets/fonts/telelower.ttf");
    m_save.setFont(m_font);
    m_save.setString(sf::String("SAVE"));
    m_save.setCharacterSize(40);
    m_save.setColor(sf::Color::White);
    sf::FloatRect saveRect = m_save.getLocalBounds();
    m_save.setOrigin(saveRect.left + saveRect.width/2.0f,
                         saveRect.top + saveRect.height/2.0f);
    m_save.setPosition(game->window.getSize().x/2.0f,350.0f);
    //set up input place
    m_name.setFont(m_font);
    m_name.setCharacterSize(20);
    m_name.setColor(sf::Color::White);
    m_name.setString(sf::String("Enter your name"));
    sf::FloatRect nameRect = m_name.getLocalBounds();
    m_name.setOrigin(nameRect.left + nameRect.width/2.0f,
                         nameRect.top + nameRect.height/2.0f);
    m_name.setPosition(game->window.getSize().x*1.0f/2.0f ,400.0f);
     //Button setup
    m_textureButtonOri.loadFromFile("assets/textures/original.png");
    m_textureButtonHover.loadFromFile("assets/textures/hoovered.png");
    m_textureButtonPress.loadFromFile("assets/textures/pressed.png");

    for(int i=0;i<2;++i){
        m_Buttons[i].setTexture(m_textureButtonOri);
        m_Buttons[i].setOrigin(m_Buttons[i].getLocalBounds().left + m_Buttons[i].getLocalBounds().width/2.0f,
                                   m_Buttons[i].getLocalBounds().top + m_Buttons[i].getLocalBounds().height/2.0f);
        m_Buttons[i].setScale(0.8f,0.5f);
        m_Buttons[i].setPosition(game->window.getSize().x /2.0f,500+50.0f *i);
    }


    std::string str[2];
    str[0] ="save";
    str[1] ="exit";
    for(int i=0;i<2;++i){
        m_Label[i].setFont(m_font);
        m_Label[i].setFillColor(sf::Color::Blue);
        m_Label[i].setCharacterSize(18);
        m_Label[i].setString(str[i]);
        sf::FloatRect labelrect = m_Label[i].getLocalBounds();
        m_Label[i].setOrigin(labelrect.left+labelrect.width/2.0f,
                                 labelrect.top+labelrect.height/2.0f);
        m_Label[i].setPosition(game->window.getSize().x/2.0f,500+50.0f *i );
    }

}

SaveState::~SaveState()
{
    //dtor
}
void SaveState::Draw(const float dt){
    game->window.clear();
    game->window.draw(m_save);
    game->window.draw(m_name);
    for(int i=0;i<2;++i){
        game->window.draw(m_Buttons[i]);
        game->window.draw(m_Label[i]);
    }


}
void SaveState::Update(const float dt){
    sf::FloatRect yourNameRect = m_name.getLocalBounds();
    m_name.setOrigin(yourNameRect.left + yourNameRect.width/2.0f,
                         yourNameRect.top + yourNameRect.height/2.0f);
    m_name.setPosition(game->window.getSize().x/2.0f,400.0f);
}
void SaveState::HandleInput(){
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
            break;
        case sf::Event::TextEntered:
            if(event.text.unicode<128){
                s_str+=static_cast<char>(event.text.unicode);
                m_name.setString(sf::String(s_str));
            }
            break;
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
                        case 0:{
                            m_tetro.Save(s_str);
                            std::ofstream file;
                            file.open("SavedFile.txt",std::ios_base::app);
                            file<<s_str<<std::endl;
                            if(m_Buttons[i].getGlobalBounds().contains(mousePosF))
                                m_Buttons[i].setTexture(m_textureButtonHover);
                            else
                                m_Buttons[i].setTexture(m_textureButtonOri);

                            game->popState();
                            game->popState();
                            break;
                        }

                        case 1:{
                            if(m_Buttons[i].getGlobalBounds().contains(mousePosF))
                                m_Buttons[i].setTexture(m_textureButtonHover);
                            else
                                m_Buttons[i].setTexture(m_textureButtonOri);
                            game->popState();
                            break;
                        }

                    }

                }
            }
            break;
        }
    }
}
