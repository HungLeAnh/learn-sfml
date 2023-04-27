#ifndef GAME_STATE_START_HPP
#define GAME_STATE_START_HPP

#include <SFML/Graphics.hpp>

#include "GameState.hpp" //we will be deriving this abstract classes functions.

enum States{
    Play=0,
    Credit
};
class MenuState : public GameState  //make GameState functions public to this class so we can derive it's functions.
{
public:
    //constructor (compiler will automatically make a default one)
    MenuState(Game* game);
    ~MenuState();
    //the three functions are teh three things we must do.
    virtual void draw(const float dt);
    virtual void update(const float dt);
    virtual void handleInput();
    void MouseClick();

private:
    //let's make a view for this just in case we want it

    sf::Font mFont;
    sf::Text mText;

    sf::Vector2f mButtonSize;
    sf::Vector2f mButtonPos;
    unsigned int mButtomPadding;

    sf::RectangleShape mRects[3];
    sf::Text mLabel[3];
    sf::Event mEvent;
    //this will be used to change the game state to the "Play the actual fucking game" state.
    void loadstate(int state);
};

#endif /* GAME_STATE_START_HPP */
