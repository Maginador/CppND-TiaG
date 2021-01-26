//
//  Renderer.cpp
//  This Is a Game
//
//  Created by Ricardo Marginador on 25/01/21.
//

#include "Renderer.hpp"
#include "Assets.hpp"
//TODO: Replace placeholder Renderable by a list of renderables with add/remove system
Renderable *rend = nullptr;

void Renderer::render(){
    SDL_RenderClear(renderer);
    
    //TODO: Create list of renderable objects and loop rendering
    SDL_RenderCopy(renderer, rend->_texture, NULL, rend->_transform);
    
    SDL_RenderPresent(renderer);
}
void Renderer::clean(){
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
}
bool Renderer::init(const char *title, int xpos, int ypos, int width, int height, int flags){
    window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
    if(window){
        std::cout<< "Window Created" << std::endl;
    }else{
        std::cout<< "Error creating Window"<<std::endl << SDL_GetError()<<std::endl;
        return false;
    }
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
    if(renderer){
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        std::cout<< "Renderer Created"<< std::endl;
    }else{
        std::cout<< "Error creating Renderer"<<std::endl << SDL_GetError()<<std::endl;
        return false;
    }
    
    //Placeholder texture TODO: Remove placeholder and create system for external addition
    Assets asset = Assets();
    //TODO: Remove New
    rend = new Renderable(asset.loadAsset(renderer, "assets/sample.png"), 60, 60, 0, 0);
    
    return true;
}

//TODO: create lists of custom structure for animations and states
Renderable::Renderable(SDL_Texture *texture, int width, int height, int initX, int initY){
    _texture = texture;
    //TODO: Remove New
    _transform = new SDL_Rect();
    _transform->w = width;
    _transform->h = height;
    _transform->x = initX;
    _transform->y = initY;

};
