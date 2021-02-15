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
#include "UserInterface.hpp"
#include <chrono>
#include <random>
#include "Constants.hpp"
class GameObject;
class Physics;
class Vector2;

using std::vector;




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
    void removeBulletToList(Character *bullet);
    void updateCurrency(int currency);
private:
    void setupUI();
    void createGameGrid();
    void createCursor();
    void enemySpawner();
    void enemyTimmedSpawnning();
    void placeTower(Vector2 gridSlot);
    bool isRunning;
    int currency=100;
    Renderer *renderer;
    Input *input;
    Physics *physics;
    UserInterface *UI;
    vector<Character*> _enemies;
    vector<Character*> _towers;
    vector<Character*> _bullets;

    int slotsGrid[GRID_WIDTH * GRID_HEIGHT];
    
};

#endif /* Game_hpp */
