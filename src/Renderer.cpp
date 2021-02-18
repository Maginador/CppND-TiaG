//
//  Renderer.cpp
//  This Is a Game
//
//  Created by Ricardo Marginador on 25/01/21.
//

#include "Renderer.hpp"
Renderer* Renderer::instance = 0;
SDL_Renderer* Renderer::renderer = 0;

Renderer::Renderer(){
    //Lazy initializtion
    if(instance == nullptr)
        instance = this;
}
void Renderer::render(){
    
    runScheduledDelete();
    SDL_LockMutex( rendererMtx );
    SDL_RenderClear(renderer);

    for(int i =0; i<renderablesList.size();i++){
        
        
        if(!renderablesList[i] || !renderablesList[i]->_texture){
            continue;
        }
        SDL_RenderCopy(renderer, renderablesList[i]->_texture, NULL, renderablesList[i]->_transform);
    }
    
    for(int i =0; i<uielementsList.size();i++){
        
        
        if(!uielementsList[i] || !uielementsList[i]->_texture){
            continue;
        }
        SDL_RenderCopy(renderer, uielementsList[i]->_texture, NULL, uielementsList[i]->_transform);
    }
    SDL_RenderPresent(renderer);
    SDL_UnlockMutex( rendererMtx );
    

}

void Renderer:: addDeleteToSchedule(Renderable *obj){
    scheduledDelete.emplace_back(obj);
}
void Renderer::runScheduledDelete(){
    
    for(int i =0; i< scheduledDelete.size(); i++){
        
        removeRenderableFromList(scheduledDelete[i]);
        
    }
    scheduledDelete.clear();
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
    
    //TODO: Remove New
    
    
    cursor.x = 50;
    cursor.y = 100;
    cursor.w = 0;
    cursor.h = 0;
    return true;
}

void Renderer::removeRenderableFromList(Renderable *obj){
    for(int i =0; i<renderablesList.size(); i++) if(renderablesList[i] == obj){
        renderablesList.erase(renderablesList.begin() + i);
        //renderablesList[i] = nullptr;
        delete(obj);
    }
}
void Renderer::addRenderableToList(Renderable *obj){
    SDL_LockMutex(Renderer::instance->rendererMtx);
        renderablesList.emplace_back(obj);
    SDL_UnlockMutex(Renderer::instance->rendererMtx);

}
void Renderer::addUIElementToList(Renderable *obj){
    SDL_LockMutex(Renderer::instance->rendererMtx);
        uielementsList.emplace_back(obj);
    SDL_UnlockMutex(Renderer::instance->rendererMtx);

}

Renderable* Renderer::createUIRenderable(const char *assetPath, int width, int height, int x = 0, int y = 0){
    Assets asset = Assets();
    
    Renderable* rend = new Renderable(asset.loadAsset(renderer, assetPath), width, height, x, y);
    uielementsList.emplace_back(rend);
    return std::move(rend);
}


Renderable* Renderer::createRenderable(const char *assetPath, int width, int height, int x = 0, int y = 0){
    Assets asset = Assets();
    
    Renderable* rend = new Renderable(asset.loadAsset(renderer, assetPath), width, height, x, y);
    renderablesList.emplace_back(rend);
    return std::move(rend);
}

SDL_Texture* Renderer::createTexture(const char *assetPath){
    Assets asset = Assets();
    SDL_Texture* texture = asset.loadAsset(renderer, assetPath);
    
    return std::move(texture);
}

SDL_Renderer* Renderer::getRenderer(){

    return renderer;
}

//TODO: create lists of custom structure for animations and states
Renderable::Renderable(SDL_Texture *texture, int width, int height, int initX, int initY){
    SDL_LockMutex(Renderer::instance->rendererMtx);
    _texture = texture;
    //TODO: Remove New
    _transform = new SDL_Rect();
    _transform->w = width;
    _transform->h = height;
    _transform->x = initX;
    _transform->y = initY;
    SDL_UnlockMutex(Renderer::instance->rendererMtx);
};
Renderable::~Renderable(){
    std::cout<< "Deconstructor for Renderable" << std::endl;
    //SDL_DestroyTexture(_texture);
    //_transform = nullptr;
}
