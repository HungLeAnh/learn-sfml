#ifndef WINDOW_HPP
#define WINDOW_HPP

#include<EventManager.hpp>

class Window
{
    public:
        Window();
        Window(const std::string& l_title,const sf::Vector2u& l_size);
        ~Window();
        void BeginDraw();
        void EndDraw();
        void Update();
        bool IsDone();
        bool IsFullScreen();
        bool IsFocused();
        sf::Vector2u GetWindowSize();
        EventManager* GetEventManager();
        void ToggleFullScreen(EventDetails* l_details);
        void Close(EventDetails* l_details =nullptr);
        void Draw(sf::Drawable& l_drawable);
        sf::RenderWindow* GetRenderWindow();

    private:
        void Setup(const std::string& l_title,const sf::Vector2u& l_size);
        void Destroy();
        void Create();
        sf::RenderWindow m_window;
        sf::Vector2u m_windowSize;
        std::string m_windowTitle;
        bool m_IsDone;
        bool m_IsFullScreen;
        EventManager m_eventManager;
        bool m_isFocused;
};

#endif // WINDOW_HPP
