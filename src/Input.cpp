//
//  Input.cpp
//  TiaG
//
//  Created by Ricardo Marginador on 27/01/21.
//

#include "Input.hpp"

Input* Input::instance = 0;
Input::Input(){
    if(instance == nullptr)
        instance = this;
};
Input::~Input(){};
Input::inputKey Input::getKeyDown(){
    if(instance != nullptr)
        return instance->keyDown;
    else
        return Input::inputKey::none;

}

void Input::handleEvents(){
        SDL_Event event;
        SDL_PollEvent(&event);
            
            if(event.type == SDL_KEYDOWN){
                switch( event.key.keysym.sym ){
                    case SDLK_UP:
                    keyDown = inputKey::up;
                        break;

                    case SDLK_DOWN:
                    keyDown = inputKey::down;
                        break;

                    case SDLK_LEFT:
                   keyDown = inputKey::left;
                        break;

                    case SDLK_RIGHT:
                    keyDown = inputKey::right;
                        break;
                    
                    case SDLK_SPACE :
                        keyDown = inputKey::space;
                        break;
                    
                    case SDLK_f :
                        keyDown = inputKey::f;
                        break;
                        
                    case SDLK_e :
                        keyDown = inputKey::e;
                        break;
                        
                    case SDLK_q :
                        keyDown = inputKey::q;
                        break;
                        
                    case SDLK_ESCAPE :
                        keyDown = inputKey::esc;
                        break;
                        
                    default:
                    keyDown = inputKey::none;
                        break;
                    }
            }
            else {
                keyDown = inputKey::none;
        }
    }
