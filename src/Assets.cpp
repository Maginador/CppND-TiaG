//
//  Media.cpp
//  This Is a Game
//
//  Created by Ricardo Marginador on 25/01/21.
//

#include "Assets.hpp"

Assets* Assets::instance = 0;
Assets::Assets(){
    if(instance == nullptr)
    instance = this;
    
}

Assets::~Assets(){};
SDL_Texture* Assets::loadAsset(SDL_Renderer* renderer, const char *path){
    
    SDL_Texture *texture = NULL;
    
    SDL_Surface *tempSurface = IMG_Load(path);
    
    if(tempSurface == NULL){
        std::cout<<"Error loading asset " << std::endl << SDL_GetError()<<std::endl;
    }else{
        texture = SDL_CreateTextureFromSurface(renderer, tempSurface);
        
        if(texture == NULL){
            std::cout<<"Error loading asset " << std::endl << SDL_GetError()<<std::endl;
        }else{
            //release temporary surface
            SDL_FreeSurface(tempSurface);
            return texture;
        }
    }
    
    return NULL;
    
}

void Assets::addFont(string id, const char* path, int fontSize){
    fonts.emplace(id, TTF_OpenFont(path, fontSize));
    std::cout << "Fonts available : "<<fonts.size()<<std::endl;
}
TTF_Font* Assets::getFont(string id){
    return fonts[id];
}
