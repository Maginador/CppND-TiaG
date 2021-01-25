//
//  main.cpp
//  This Is a Game
//
//  Created by Ricardo Marginador on 24/01/21.
//

#include <iostream>
#include "Game.hpp"


//Screen dimension constants
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
Game *game = nullptr;
Assets *assets = nullptr;
int main() {
    
    game = new Game();
    assets = new Assets();
    
    game->init("TiaG", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, false);
    SDL_Delay(1000);
    while(game->running()){
        
        game->handleEvents();
        game->update();
        
        //media->loadAsset("rsc/sample.bmp");
    
        
    }
    
    
}
