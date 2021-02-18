//
//  main.cpp
//  This Is a Game
//
//  Created by Ricardo Marginador on 24/01/21.
//

#include <iostream>
#include "Game.hpp"
#include "SDL2.SDL.h" 
#include "Constants.hpp"

unique_ptr<Game> game = nullptr;
unique_ptr<Assets> assets = nullptr;
unique_ptr<Input> input = nullptr;

int main() {
    
    
    Uint32 frameStart;
    int frameTime;
    
    input = std::make_unique<Input>();
    game = std::make_unique<Game>();
    assets = std::make_unique<Assets>();
    //TODO: make it possible to adjust values
    game->init("TiaG", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, false);
    
    while(game->running()){
        Time::update();
        frameStart = SDL_GetTicks();
        input->handleEvents();
        game->windowEvents();
        game->update();
        
        frameTime = SDL_GetTicks() - frameStart;
        
        if(SCREEN_TICKS_PER_FRAME > frameTime){
            SDL_Delay(SCREEN_TICKS_PER_FRAME - frameTime);
        }
    }
    
    
}


