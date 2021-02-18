//
//  Media.hpp
//  This Is a Game
//
//  Created by Ricardo Marginador on 25/01/21.
//

#ifndef Assets_hpp
#define Assets_hpp

#include <iostream>
#include <map>
#include "SDL2.SDL.h" 
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"
#include "Renderer.hpp"

using std::string;

class Assets{
    
    public :
    
    static Assets *instance;
    Assets();
    ~Assets();
    SDL_Texture* loadAsset(SDL_Renderer* renderer, const char *path);
    void addFont(string id, const char* path, int fontSize);
    TTF_Font* getFont(string id);
    
    
    private :
    std::map<string, SDL_Texture*> textures;
    std::map<string, TTF_Font*> fonts;
};
#endif /* Assets_hpp */
