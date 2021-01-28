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
        //TODO: Remove New (Use shared_ptr instead of raw pointer)
        renderer = new Renderer();
        renderer->init(title, xpos, ypos, width, height, flags);
        //TODO: Remove New (Use unique_ptr instead of raw pointer)
        input = new Input();
        isRunning = true;
    }else{
        isRunning = false;
    }
}

void Game::handleEvents(){
    SDL_Event event;
    SDL_PollEvent(&event);
        if(event.type ==  SDL_QUIT)
            isRunning=false;
        else if(event.type == SDL_KEYDOWN){
            switch( event.key.keysym.sym ){
                case SDLK_UP:
                    input->keyDown = Input::inputKey::up;
                    break;

                    case SDLK_DOWN:
                    input->keyDown = Input::inputKey::down;
                    break;

                    case SDLK_LEFT:
                    input->keyDown = Input::inputKey::left;
                    break;

                    case SDLK_RIGHT:
                    input->keyDown = Input::inputKey::right;
                    break;

                    default:
                    input->keyDown = Input::inputKey::none;
                    break;
                }
        }
        else {
            input->keyDown = Input::inputKey::none;
    }
}

void Game::update(){
    renderer->render();
    
    
    //Move Cursor
    if(Input::getKeyDown() == Input::inputKey::down){
        renderer->cursor.y += 10;
    }
    else if(Input::getKeyDown() == Input::inputKey::up){
        renderer->cursor.y -= 10;
    }
    else if(Input::getKeyDown() == Input::inputKey::right){
        renderer->cursor.x += 10;
    }
    else if(Input::getKeyDown() == Input::inputKey::left){
        renderer->cursor.x -= 10;
    }
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


