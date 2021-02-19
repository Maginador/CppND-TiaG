//
//  Renderer.hpp
//  This Is a Game
//
//  Created by Ricardo Marginador on 25/01/21.
//

#ifndef Renderer_hpp
#define Renderer_hpp

#include <iostream>
#include "SDL2/SDL.h" 
#include "SDL2/SDL_image.h"
#include <vector>
#include "Assets.hpp"
#include <memory>

class Renderable{
    public :
    Renderable(){};
    Renderable(SDL_Texture *texture, int width, int height, int initX, int initY);
    ~Renderable();
    SDL_Texture *_texture;
    SDL_Rect *_transform;
    private :
    
};
class Renderer{
  
    public :
    Renderer();
    ~Renderer();
    static Renderer *instance;
    void render();
    void clean();
    //TODO: Replace with shared_ptr
    std::shared_ptr<Renderable> createUIRenderable(const char *assetPath, int width, int height, int x, int y);
    std::shared_ptr<Renderable> createRenderable(const char *assetPath, int width, int height, int x, int y);
    static SDL_Texture* createTexture (const char *assetPath);
    bool init(const char *title, int xpos, int ypos, int width, int height, int flags);
    SDL_Renderer* getRenderer();
    SDL_Rect cursor;
    void addUIElementToList(std::shared_ptr<Renderable> obj);
    void addRenderableToList(std::shared_ptr<Renderable> obj);
    void addDeleteToSchedule(std::shared_ptr<Renderable> obj);
    void removeRenderableFromList(std::shared_ptr<Renderable> obj);
    void runScheduledDelete();
    SDL_mutex* rendererMtx = SDL_CreateMutex();

    private :
    //TODO: Replace with shared_ptr
    std::vector<std::shared_ptr<Renderable>> renderablesList;
    std::vector<std::shared_ptr<Renderable>> uielementsList;
    std::vector<std::shared_ptr<Renderable>> scheduledDelete;
    
    static SDL_Renderer *renderer;
    SDL_Window *window;

    
};
#endif /* Renderer_hpp */
