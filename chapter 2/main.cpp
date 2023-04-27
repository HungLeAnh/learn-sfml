#include<Game.hpp>

#include<iostream>

int main(int argc,void** argv[]){
    Game game;
    while(!game.GetWindow()->IsDone()){
        game.HandleInput();
        game.Update();
        game.Render();
        sf::sleep(sf::seconds(0.2));
        game.RestartClock();
    }
}
