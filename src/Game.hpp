//
//  Game.hpp
//  This Is a Game
//
//  Created by Ricardo Marginador on 25/01/21.
//

#ifndef Game_hpp
#define Game_hpp

#include <iostream>
#include <thread>
#include <vector>
#include "Assets.hpp"
#include "Input.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_thread.h>
#include "Renderer.hpp"
#include "GameObject.hpp"
#include "Physics.hpp"
#include "Character.hpp"
#include "UserInterface.hpp"
#include <chrono>
#include <random>
#include "Constants.hpp"
#include "Time.hpp"
class GameObject;
class Physics;
class Vector2;

using std::vector;




//Foward reference for circle header include
class Character;
class Enemy;
class Bullet;
class Tower;

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
    void addBulletToList(Bullet *bullet);
    void removeCharacterFromList(Character *character);
    void updateCurrency(int currency);
    void runGameOver();
    void cleanSlot(Vector2 slot);
    SDL_mutex* towerMutex = SDL_CreateMutex();
private:
    void setupUI();
    void createGameGrid();
    void createFactories();
    void createCursor();
    void createBackground();
    void enemyTimmedSpawnning();
    void placeTower(Vector2 gridSlot);
    bool isRunning;
    int currency=100;
    std::unique_ptr<Renderer> renderer;
    std::unique_ptr<Input> input;
    std::unique_ptr<Physics> physics;
    std::unique_ptr<UserInterface> UI;
    vector<Enemy*> _enemies;
    vector<Tower*> _towers;
    vector<Bullet*> _bullets;
    bool gameOver = false;

    int slotsGrid[GRID_WIDTH * GRID_HEIGHT];
    
    
    //Thread Methods
    static int enemySpawner(void* data);

};

#endif /* Game_hpp */
