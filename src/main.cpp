//
//  main.cpp
//  This Is a Game
//
//  Created by Ricardo Marginador on 24/01/21.
//

#include <iostream>
#include "Game.hpp"


//Screen dimension constants
const int SCREEN_WIDTH = 1024;
const int SCREEN_HEIGHT = 768;
//TODO: Replace pointer with unique_ptr
Game *game = nullptr;
Assets *assets = nullptr;
int main() {
    
    //TODO: Remove New
    
    game = new Game();
    assets = new Assets();
    //TODO: make it possible to adjust values
    game->init("TiaG", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, false);
    SDL_Delay(1000);
    while(game->running()){
        
        //TODO: create Input System (Input.cpp)
        game->handleEvents();
        //TODO: create FPS Control (Time.cpp)
        game->update();
        
        //TODO: Add Physics processing
    
        auto debug = Input::getKeyDown();
        if(debug != 0)
        std::cout << debug<<std::endl;
        
    }
    
    
}
