#include "Game.hpp"
#include "IntroState.hpp"
//#include "MenuState.hpp"

int main()
{
    Game game; //create game object (so far this constructor just intiializes our window)

    //we will call our menu class "MenuState"
    game.pushState(new IntroState(&game));  //we want to create a pointer at the game objects address. this will enter our menu.

    //now loop our game.
    game.gameLoop();

    return 0;
}
