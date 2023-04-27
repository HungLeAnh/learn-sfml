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
void Window::Setup(const std::string& l_title,const sf::Vector2u& l_size){
    m_windowTitle = l_title;
    m_windowSize=l_size;
    m_IsFullScreen=false;
    m_IsDone=false;
    m_isFocused=true;
    Create();
    m_isFocused = true;
    m_eventManager.AddCallback("Fullscreen_toggle",&Window::ToggleFullScreen,this);
    m_eventManager.AddCallback("Window_close",&Window::Close,this);
}
void Window::Create(){
    auto style = (m_IsFullScreen?sf::Style::Fullscreen : sf::Style::Default);
    m_window.create({m_windowSize.x,m_windowSize.y,32},m_windowTitle,style);
}
void Window::Destroy(){
    m_window.close();
}
void Window::Update(){
    sf::Event event;
    while(m_window.pollEvent(event)){
        if(event.type == sf::Event::LostFocus){
            m_isFocused =false;
            m_eventManager.SetFocus(false);
        }
        else if(event.type == sf::Event::GainedFocus){
            m_isFocused = true;
            m_eventManager.SetFocus(true);
        }
        m_eventManager.HandleEvent(event);
    }
    m_eventManager.Update();
}
void Window::ToggleFullScreen(EventDetails* l_details){
    m_IsFullScreen = !m_IsFullScreen;
    Destroy();
    Create();
}
sf::RenderWindow* Window::GetRenderWindow(){ return &m_window; }
void Window::BeginDraw(){
    m_window.clear(sf::Color::Black);
}
EventManager* Window::GetEventManager(){
    return &m_eventManager;
}
void Window::EndDraw(){
    m_window.display();
}
bool Window::IsDone(){
    return m_IsDone;
}
bool Window::IsFullScreen(){
    return m_IsFullScreen;
}
sf::Vector2u Window::GetWindowSize(){
    return m_windowSize;
}
void Window::Draw(sf::Drawable& l_drawable){
    m_window.draw(l_drawable);
}
void Window::Close(EventDetails* l_details ){
    l_details=nullptr;
    m_IsDone = true;
}
