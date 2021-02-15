//
//  Game.cpp
//  This Is a Game
//
//  Created by Ricardo Marginador on 25/01/21.
//

#include "Game.hpp"


Game* Game::instance = 0;

Renderable *cursor;
Renderable *uielement;
Vector2 cursorGridPos;
std::chrono::milliseconds timer;
std::chrono::time_point<std::chrono::system_clock> lastSpawn;
Game::Game(){
    if(instance == nullptr)
        instance = this;
}

Game::~Game(){
    
}

void Game::init(const char *title, int xpos, int ypos, int width, int height, bool fullscreen){
    
    
    int flags = fullscreen ? SDL_WINDOW_FULLSCREEN : 0;
    
    if(SDL_Init(SDL_INIT_EVERYTHING) == 0 && TTF_Init() == 0){
        std::cout<< "SDL Subsystens Initialized..."<< std::endl;
        //TODO: Remove New (Use shared_ptr instead of raw pointer)
        renderer = new Renderer();
        renderer->init(title, xpos, ypos, width, height, flags);
        //TODO: Remove New (Use unique_ptr instead of raw pointer)
        input = new Input();
        isRunning = true;
        
        physics = new Physics();
        Assets::instance->addFont("arial", "fonts/arial.ttf", 50);
    }else{
        isRunning = false;
    }
    
    //Create cursor
    createGameGrid();
    createCursor();
    lastSpawn = std::chrono::system_clock::now();
    timer = std::chrono::milliseconds(3000);

    
    //Debug UI
    
    SDL_Color color = {255,0,0,255};
    uielement = new UIElement(120, 120, "Debug Text2", "arial", color);
    renderer->addRenderableToList(uielement);

}

void Game::windowEvents(){
    SDL_Event event;
    SDL_PollEvent(&event);
        if(event.type ==  SDL_QUIT)
            isRunning=false;
        else {
            input->keyDown = Input::inputKey::none;
    }
}

void Game::update(){
    std::cout <<uielement->_texture << std::endl;
    renderer->render();
    physics->simulate();
    //Move Cursor
    if(Input::getKeyDown() == Input::inputKey::down && cursor->_transform->y < CURSOR_INIT_POSITION_Y + MOVE_INTENSITY_Y * GRID_HEIGHT){
        cursor->_transform->y += MOVE_INTENSITY_Y;
        cursorGridPos._y +=1;
    }
    else if(Input::getKeyDown() == Input::inputKey::up && cursor->_transform->y > CURSOR_INIT_POSITION_Y){
        cursor->_transform->y -= MOVE_INTENSITY_Y;
        cursorGridPos._y -=1;
    }
    else if(Input::getKeyDown() == Input::inputKey::right && cursor->_transform->x < CURSOR_INIT_POSITION_X + MOVE_INTENSITY_X * GRID_WIDTH){
        cursor->_transform->x += MOVE_INTENSITY_X;
        cursorGridPos._x +=1;
    }
    else if(Input::getKeyDown() == Input::inputKey::left && cursor->_transform->x > CURSOR_INIT_POSITION_X){
        cursor->_transform->x -= MOVE_INTENSITY_X;
        cursorGridPos._x -=1;
    }
    else if(Input::getKeyDown() == Input::inputKey::space){
        placeTower(cursorGridPos);
    }
    
    //Update enemies
    for(int i =0; i<_enemies.size(); i++){
        if(!_enemies[i]) _enemies.erase(_enemies.begin()+i);
        _enemies[i]->act();
    }
    for(int i =0; i<_towers.size(); i++){
        if(!_towers[i]) _towers.erase(_towers.begin()+i);
        _towers[i]->act();
    }
    for(int i =0; i<_bullets.size(); i++){
        if(!_bullets[i]) _bullets.erase(_bullets.begin()+i);
        _bullets[i]->act();
    }
    enemyTimmedSpawnning();
}

bool Game::running(){
    return isRunning;
}

void Game::createGameGrid(){
    SDL_Texture *texture = renderer->createTexture("assets/pixelSlot.png");
    //grid iteration
    for(int i =0; i<GRID_WIDTH; i++){
        for(int o =0; o<GRID_HEIGHT; o++){
            GameObject *go = new GameObject("Environment_Slot", Vector2(CURSOR_INIT_POSITION_X + (i*MOVE_INTENSITY_X), CURSOR_INIT_POSITION_Y + (o*MOVE_INTENSITY_Y)), texture, Vector2(80,80), false);
            renderer->addRenderableToList(go->getRenderable());
            slotsGrid[i + (GRID_WIDTH*o) ] = 0;
        }
    }

    
}

void Game::createCursor(){
    
    SDL_Texture *texture = renderer->createTexture("assets/cursor.png");

    GameObject *go = new GameObject("Cursor", Vector2(CURSOR_INIT_POSITION_X, CURSOR_INIT_POSITION_Y ), texture, Vector2(80,80), false);
    cursor = go->getRenderable();
    renderer->addRenderableToList(cursor);
    cursorGridPos._x = 0;
    cursorGridPos._y = 0;
}

//Create towers
void Game::placeTower(Vector2 gridSlot){
    
    //Placeholder Spawner
    SDL_Texture *texture = renderer->createTexture("assets/tower01.png");

    GameObject *go = new GameObject("Tower", Vector2(CURSOR_INIT_POSITION_X + (gridSlot._x*MOVE_INTENSITY_X), CURSOR_INIT_POSITION_Y + (gridSlot._y*MOVE_INTENSITY_Y)), texture, Vector2(80,80), true);
    renderer->addRenderableToList(go->getRenderable());
    Character *tower = new Character(go, Character::CharacterType::Tower);
    _towers.emplace_back(tower);
    
}

//Create enemies
void Game::enemySpawner(){
    
  
    int slot = (std::rand() % GRID_HEIGHT);
    //Placeholder Spawner
    SDL_Texture *texture = renderer->createTexture("assets/pixelEnemy.png");

    GameObject *go = new GameObject("Enemy", Vector2(ENEMY_SPAWN_X, CURSOR_INIT_POSITION_Y + (slot *MOVE_INTENSITY_Y)), texture, Vector2(80,80), true);
    renderer->addRenderableToList(go->getRenderable());
    
    Character *enemy = new Character(go, Character::CharacterType::Enemy);
    _enemies.emplace_back(enemy);
}

void Game::addBulletToList(Character *bullet){
    _bullets.emplace_back(bullet);
}
void Game::removeBulletToList(Character *bullet){
    
    Character::CharacterType type = bullet->getCharacterType();
    if(type == Character::CharacterType::Bullet){
        for(int i =0; i<_bullets.size(); i++) if(_bullets[i] == bullet) _bullets.erase(_bullets.begin() + i);
    }
    if(type == Character::CharacterType::Tower){
        for(int i =0; i<_towers.size(); i++) if(_towers[i] == bullet) _towers.erase(_towers.begin() + i);
    }
    if(type == Character::CharacterType::Enemy){
        for(int i =0; i<_enemies.size(); i++) if(_enemies[i] == bullet) _enemies.erase(_enemies.begin() + i);
    }
}

//TODO: Replace all spawnning methods by a separate class
void Game::enemyTimmedSpawnning(){
    
    
    auto timeNow = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - lastSpawn);
    if(timer<= timeNow){
        //Setup timer back
        std::chrono::milliseconds cycleTime = std::chrono::milliseconds((std::rand() %(SPAWNING_TIME_UPPER_RANGE-SPAWNING_TIME_LOWER_RANGE + 1) + SPAWNING_TIME_LOWER_RANGE));
        timer = cycleTime + timeNow;
        lastSpawn = std::chrono::system_clock::now();
        
        //Spawn Enemy
        enemySpawner();
    }
    
}

void Game::setupUI(){
    
    //Resources (Upper bar)
    
    //Guide for commands (Lower bar)
}


