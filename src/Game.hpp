//
//  Game.hpp
//  This Is a Game
//
//  Created by Ricardo Marginador on 25/01/21.
//

#ifndef Game_hpp
#define Game_hpp

#include <iostream>
#include <vector>
#include "Assets.hpp"
#include "Input.hpp"
#include <SDL2/SDL.h>
#include "Renderer.hpp"
#include "GameObject.hpp"
using std::vector;

//Constants area
const int MOVE_INTENSITY_Y = 120;
const int CURSOR_INIT_POSITION_Y = 100;

const int MOVE_INTENSITY_X = 80;
const int CURSOR_INIT_POSITION_X = 50;


const int GRID_WIDTH = 10;
const int GRID_HEIGHT = 5;

const int ENEMY_SPAWN_X = CURSOR_INIT_POSITION_X + (GRID_WIDTH * MOVE_INTENSITY_X);
const int ENEMY_SPAWN_Y = CURSOR_INIT_POSITION_Y + ((GRID_HEIGHT-1) * MOVE_INTENSITY_Y);

//End constants area

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
    void createCursor();
    void enemySpawner();
    void enemyController();
    void placeTower(Vector2 gridSlot);
    bool isRunning;
    Renderer *renderer;
    Input *input;
    
    vector<GameObject*> _enemies;
    int slotsGrid[GRID_WIDTH * GRID_HEIGHT];
    
};

#endif /* Game_hpp */
