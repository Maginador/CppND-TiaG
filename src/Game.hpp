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
#include "Physics.hpp"
#include "Character.hpp"
#include <chrono>
#include <random>

class GameObject;
class Physics;
class Vector2;

using std::vector;

//Constants area
const int MOVE_INTENSITY_Y = 130;
const int CURSOR_INIT_POSITION_Y = 150;

const int MOVE_INTENSITY_X = 100;
const int CURSOR_INIT_POSITION_X = 150;


const int GRID_WIDTH = 8;
const int GRID_HEIGHT = 5;

const int ENEMY_SPAWN_X = CURSOR_INIT_POSITION_X + (GRID_WIDTH * MOVE_INTENSITY_X);
const int ENEMY_SPAWN_Y = ((GRID_HEIGHT-1) * MOVE_INTENSITY_Y);

const int SPAWNING_TIME_LOWER_RANGE = 4;
const int SPAWNING_TIME_UPPER_RANGE = 15;

const int FRAMES_PER_SECOND = 60;
const int SCREEN_TICKS_PER_FRAME = 1000/FRAMES_PER_SECOND;


//End constants area


//Foward reference for circle header include
class Character;

class Game{
    
public:
    Game();
    ~Game();
    static Game *instance;
    void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
    
    void windowEvents();
    void update();
    bool running();
    
    //Public calls enabled for static instance
    void addBulletToList(Character *bullet);
    
private:
    void setupUI();
    void createGameGrid();
    void createCursor();
    void enemySpawner();
    void enemyTimmedSpawnning();
    void placeTower(Vector2 gridSlot);
    bool isRunning;
    Renderer *renderer;
    Input *input;
    Physics *physics;
    
    vector<Character*> _enemies;
    vector<Character*> _towers;
    vector<Character*> _bullets;

    int slotsGrid[GRID_WIDTH * GRID_HEIGHT];
    
};

#endif /* Game_hpp */
