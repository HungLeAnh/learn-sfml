#include "Window.hpp"

Window::Window()
{
    Setup("",sf::Vector2u(640,480));
}
Window::Window(const std::string& l_title,const sf::Vector2u& l_size){
    Setup(l_title,l_size);
}
Window::~Window()
{
    Destroy();
}
void Window::Setup(const std::string& l_title, const sf::Vector2u& l_size){
    mWindowTitle=l_title;
    mWindowSize=l_size;
    mIsFullScreen=false;
    mIsDone=false;
    Create();
}
void Window::Create(){
    auto style= (mIsFullScreen ? sf::Style::Fullscreen : sf::Style::Default);
    mWindow.create({mWindowSize.x,mWindowSize.y,32},mWindowTitle,style);
}
void Window::Destroy(){
    mWindow.close();
}
void Window::Update(){
    sf::Event event;
    while(mWindow.pollEvent(event)){
        if(event.type == sf::Event::Closed){
            mIsDone=true;
        }
        else if(event.type == sf::Event::KeyPressed &&
                event.key.code == sf::Keyboard::F5){
            ToggleFullScreen();
        }
    }
}
void Window::ToggleFullScreen(){
    mIsFullScreen =!mIsFullScreen;
    Destroy();
    Create();
}
void Window::BeginDraw(){
    mWindow.clear(sf::Color::Black);
}
void Window::EndDraw(){
    mWindow.display();
}
bool Window::IsDone(){ return mIsDone; }
bool Window::IsFullScreen(){ return mIsFullScreen; }
sf::Vector2u Window::GetWindowSize(){ return mWindowSize; }
void Window::Draw(sf::Drawable& l_drawable){
    mWindow.draw(l_drawable);
}
