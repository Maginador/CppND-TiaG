//
//  main.cpp
//  This Is a Game
//
//  Created by Ricardo Marginador on 24/01/21.
//

#include <iostream>
#include "Game.hpp"
#include <SDL2/SDL.h>

//Screen dimension constants
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 920;
//TODO: Replace pointer with unique_ptr
Game *game = nullptr;
Assets *assets = nullptr;
Input *input = nullptr;

int main() {
    
    
    Uint32 frameStart;
    int frameTime;
    
    //TODO: Remove New
    input = new Input();
    game = new Game();
    assets = new Assets();
    //TODO: make it possible to adjust values
    game->init("TiaG", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, false);
    SDL_Delay(1000);
    while(game->running()){
        
        frameStart = SDL_GetTicks();
        input->handleEvents();
        game->windowEvents();
        //TODO: create FPS Control (Time.cpp)
        game->update();
        
        //TODO: Add Physics processing
        frameTime = SDL_GetTicks() - frameStart;
        
        if(SCREEN_TICKS_PER_FRAME > frameTime){
            SDL_Delay(SCREEN_TICKS_PER_FRAME - frameTime);
        }
    }
    
    
}


