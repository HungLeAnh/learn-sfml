#ifndef WINDOW_HPP
#define WINDOW_HPP

#include<SFML/Graphics.hpp>
#include<SFML/Window.hpp>
#include<SFML/System.hpp>

class Window
{
    public:
        Window();
        Window(const std::string& l_title, const sf::Vector2u& l_size);
        ~Window();

        void BeginDraw();
        void EndDraw();
        void Update();
        bool IsDone();
        bool IsFullScreen();
        sf::Vector2u GetWindowSize();
        void ToggleFullScreen();
        void Draw(sf::Drawable& l_drawable);

    private:
        void Setup(const std::string& l_title, const sf::Vector2u& l_size);
        void Destroy();
        void Create();
        sf::RenderWindow mWindow;
        sf::Vector2u mWindowSize;
        std::string mWindowTitle;
        bool mIsDone;
        bool mIsFullScreen;

};

#endif // WINDOW_HPP
