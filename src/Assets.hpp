//
//  Media.hpp
//  This Is a Game
//
//  Created by Ricardo Marginador on 25/01/21.
//

#ifndef Assets_hpp
#define Assets_hpp

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include "Renderer.hpp"

class Assets{
    
    public :
    SDL_Texture* loadAsset(SDL_Renderer* renderer, const char *path);
};
#endif /* Assets_hpp */
