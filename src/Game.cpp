//
//  Game.cpp
//  This Is a Game
//
//  Created by Ricardo Marginador on 25/01/21.
//

#include "Game.hpp"


Game::Game(){
    
}

Game::~Game(){
    
}

void Game::init(const char *title, int xpos, int ypos, int width, int height, bool fullscreen){
    int flags = fullscreen ? SDL_WINDOW_FULLSCREEN : 0;
    
    if(SDL_Init(SDL_INIT_EVERYTHING) == 0){
        std::cout<< "SDL Subsystens Initialized..."<< std::endl;
        //TODO: Remove New
        renderer = new Renderer();
        renderer->init(title, xpos, ypos, width, height, flags);

        isRunning = true;
    }else{
        isRunning = false;
    }
}

void Game::handleEvents(){
    SDL_Event event;
    SDL_PollEvent(&event);
    switch (event.type) {
        case SDL_QUIT:
            isRunning=false;
            break;
            
        default:
            break;
    }
}

void Game::update(){
    renderer->render();
}

/*void Game::blitToScreen(SDL_Surface *surface){
    
    if(surface == nullptr)        std::cout << "Null source surface" << std::endl;

    SDL_Surface *surf = SDL_GetWindowSurface(window);
    
    if(surf == nullptr)        std::cout << "Null destination surface" << std::endl << SDL_GetError();

    if(SDL_BlitSurface(surface, NULL, surf, NULL) == 0){
        std::cout << "Blit Sucess" << std::endl;
        
    }else{
        std::cout << "Blit Error" << std::endl<<SDL_GetError()<<std::endl;
    }
}
void Game::render(){
    SDL_RenderClear(renderer);
    
    SDL_RenderPresent(renderer);
}
*/


bool Game::running(){
    return isRunning;
}


