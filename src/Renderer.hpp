//
//  Renderer.hpp
//  This Is a Game
//
//  Created by Ricardo Marginador on 25/01/21.
//

#ifndef Renderer_hpp
#define Renderer_hpp

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <vector>
#include "Assets.hpp"
#include <memory>

class Renderable{
    public :
    Renderable(SDL_Texture *texture, int width, int height, int initX, int initY);
    ~Renderable(){};
    SDL_Texture *_texture;
    SDL_Rect *_transform;
    private :
    
};
class Renderer{
  
    public :
    Renderer(){};
    ~Renderer(){};
    void render();
    void clean();
    //TODO: Replace with shared_ptr
    Renderable* createRenderable(char *assetPath, int width, int height, int x, int y);
    bool init(const char *title, int xpos, int ypos, int width, int height, int flags);
    SDL_Renderer* getRenderer();
    SDL_Rect cursor;
    private :
    //TODO: Replace with shared_ptr
    std::vector<Renderable*> renderablesList;
    SDL_Renderer *renderer;
    SDL_Window *window;
    
};
#endif /* Renderer_hpp */
