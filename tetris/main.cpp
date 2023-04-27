#include<iostream>

#include "Game.hpp"
#include "SplashState.hpp"

int main(){
    Game game;

    game.pushState(new SplashState(&game));
    game.gameLoop();
}
