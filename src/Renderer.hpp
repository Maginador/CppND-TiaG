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



class Renderer{
  
    public :
    Renderer(){};
    ~Renderer(){};
    void render();
    void clean();
    
    bool init(const char *title, int xpos, int ypos, int width, int height, int flags);
    SDL_Renderer* getRenderer();
    private :
    //TODO : List of renderables
    //TODO : List of renderablesRects
    SDL_Renderer *renderer;
    SDL_Window *window;
    
};

class Renderable{
    public :
    Renderable(SDL_Texture *texture, int width, int height, int initX, int initY);
    ~Renderable(){};
    SDL_Texture *_texture;
    SDL_Rect *_transform;
    private :
    
};
#endif /* Renderer_hpp */
