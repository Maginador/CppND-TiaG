//
//  Game.hpp
//  This Is a Game
//
//  Created by Ricardo Marginador on 25/01/21.
//

#ifndef Game_hpp
#define Game_hpp

#include <iostream>
#include "Assets.hpp"
#include "Input.hpp"
#include <SDL2/SDL.h>
#include "Renderer.hpp"

class Game{
    
public:
    Game();
    ~Game();
    
    void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
    
    void handleEvents();
    void update();
    bool running();
    
private:
    void createGameGrid();
    bool isRunning;
    Renderer *renderer;
    Input *input;
    
};




#endif /* Game_hpp */
