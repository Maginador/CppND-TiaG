//
//  Game.cpp
//  This Is a Game
//
//  Created by Ricardo Marginador on 25/01/21.
//

#include "Game.hpp"


Game* Game::instance = 0;

Renderable *cursor;
Vector2 cursorGridPos;
float enemyMultiplier = 1;
Game::Game(){
    if(instance == nullptr)
        instance = this;
}

Game::~Game(){
    
}

void Game::runGameOver(){
    gameOver = true;
    renderer->createUIRenderable("assets/fade.png", SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0);
    UI->gameOverScreen();
}
//Create enemies
int Game::enemySpawner(void* data){
    
    if(Time::timedAction(std::chrono::milliseconds((int)(ENEMY_SPAWN_TIME / enemyMultiplier)))){
        if(Game::instance->gameOver) return 0;
        int slot = (std::rand() % GRID_HEIGHT);
        //Placeholder Spawner
        SDL_Texture *texture = instance->renderer->createTexture("assets/pixelEnemy.png");

        GameObject *go = new GameObject("Enemy", Vector2(ENEMY_SPAWN_X, CURSOR_INIT_POSITION_Y + (slot *MOVE_INTENSITY_Y)), texture, Vector2(80,80), true, Vector2(-1,-1));
        instance->renderer->addRenderableToList(go->getRenderable().get());
        
        std::shared_ptr<Enemy> enemy = std::shared_ptr<Enemy>(new Enemy(go->getIndex()));
        //auto character = static_cast<std::shared_ptr<Character>>(enemy);
        go->addCharacter(enemy);
        instance->_enemies.emplace_back(enemy.get());
        int data = 10;
        //SDL_Thread* threadID = SDL_CreateThread(enemySpawner, "Teste", (void*)data);
        enemyMultiplier *= 1.1;
        enemySpawner(nullptr);
    }
    return 0;
}


void Game::init(const char *title, int xpos, int ypos, int width, int height, bool fullscreen){
    
    
    int flags = fullscreen ? SDL_WINDOW_FULLSCREEN : 0;
    
    if(SDL_Init(SDL_INIT_EVERYTHING) == 0 && TTF_Init() == 0){
        std::cout<< "SDL Subsystens Initialized..."<< std::endl;
        renderer = std::make_unique<Renderer>();
        renderer->init(title, xpos, ypos, width, height, flags);
        input = std::make_unique<Input>();
        isRunning = true;
        physics = std::make_unique<Physics>();
        UI = std::make_unique<UserInterface>();
        
    }else{
        isRunning = false;
    }
    _towers.reserve(50);
    createBackground();
    //Create cursor
    createGameGrid();
    createFactories();
    createCursor();
    UI->buildUI();
    UserInterface::updateTextValue("currency", std::to_string(currency));
    int data = 10;
    SDL_Thread* threadID = SDL_CreateThread(enemySpawner, "Teste", (void*)data);
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
    renderer->render();
    physics->simulate();
    UI->updateData();
    //Move Cursor
    if(!gameOver){
        if(Input::getKeyDown() == Input::inputKey::down && cursor->_transform->y < CURSOR_INIT_POSITION_Y + MOVE_INTENSITY_Y * (GRID_HEIGHT -1)){
            cursor->_transform->y += MOVE_INTENSITY_Y;
            cursorGridPos._y +=1;
        }
        else if(Input::getKeyDown() == Input::inputKey::up && cursor->_transform->y > CURSOR_INIT_POSITION_Y){
            cursor->_transform->y -= MOVE_INTENSITY_Y;
            cursorGridPos._y -=1;
        }
        else if(Input::getKeyDown() == Input::inputKey::right && cursor->_transform->x < CURSOR_INIT_POSITION_X + MOVE_INTENSITY_X * (GRID_WIDTH -1)){
            cursor->_transform->x += MOVE_INTENSITY_X;
            cursorGridPos._x +=1;
        }
        else if(Input::getKeyDown() == Input::inputKey::left && cursor->_transform->x > CURSOR_INIT_POSITION_X){
            cursor->_transform->x -= MOVE_INTENSITY_X;
            cursorGridPos._x -=1;
        }
        else if(Input::getKeyDown() == Input::inputKey::f){
            placeTower(cursorGridPos);
        }
        
        //Update enemies
        for(int i =0; i<_enemies.size(); i++){
            if(!_enemies[i]) _enemies.erase(_enemies.begin()+i);
            //SDL_CreateThread(Enemy::act, "EnemyAct", (Character*)_enemies[i]);
            _enemies[i]->act();
        }
        SDL_LockMutex( towerMutex );

        for(int i =0; i<_towers.size(); i++){
            if(!_towers[i]) _towers.erase(_towers.begin()+i);
            //SDL_CreateThread(Tower::act, "TowerAct", (Character*)_towers[i]);
            _towers[i]->act();
        }
        SDL_UnlockMutex( towerMutex );
        for(int i =0; i<_bullets.size(); i++){
            if(!_bullets[i]) _bullets.erase(_bullets.begin()+i);
            _bullets[i]->act();
        }
        
    }
//    enemyTimmedSpawnning();
}

bool Game::running(){
    return isRunning;
}

void Game::createFactories(){
    SDL_Texture *texture = renderer->createTexture("assets/factory.png");
    //grid iteration
        for(int o =0; o<GRID_HEIGHT; o++){
            GameObject *go = new GameObject("Factories", Vector2(CURSOR_INIT_POSITION_X + (-1*MOVE_INTENSITY_X), CURSOR_INIT_POSITION_Y + (o*MOVE_INTENSITY_Y)), texture, Vector2(80,80), true, Vector2(-1,o));
            renderer->addRenderableToList(go->getRenderable().get());
            Factory *factory = new class Factory(go->getIndex());
            auto character = static_cast<Character*>(factory);
            go->addCharacter(std::shared_ptr<Character>(character));
            instance->_towers.emplace_back(factory);
        }
}
void Game::createGameGrid(){
    SDL_Texture *texture = renderer->createTexture("assets/pixelSlot.png");
    //grid iteration
    for(int i =0; i<GRID_WIDTH; i++){
        for(int o =0; o<GRID_HEIGHT; o++){
            GameObject *go = new GameObject("Environment_Slot", Vector2(CURSOR_INIT_POSITION_X + (i*MOVE_INTENSITY_X), CURSOR_INIT_POSITION_Y + (o*MOVE_INTENSITY_Y)), texture, Vector2(80,80), false, Vector2(-1,-1));
            renderer->addRenderableToList(go->getRenderable().get());
            slotsGrid[i + (GRID_WIDTH*o) ] = 0;
        }
    }

    
}

void Game::createBackground(){
    
    SDL_Texture *texture = renderer->createTexture("assets/bg.png");

    GameObject *go = new GameObject("Backbround", Vector2(0, 0 ), texture, Vector2(1280,920), false, Vector2(-1,-1));
    renderer->addRenderableToList(go->getRenderable().get());
}

void Game::createCursor(){
    
    SDL_Texture *texture = renderer->createTexture("assets/cursor.png");

    GameObject *go = new GameObject("Cursor", Vector2(CURSOR_INIT_POSITION_X, CURSOR_INIT_POSITION_Y ), texture, Vector2(80,80), false, Vector2(-1,-1));
    cursor = go->getRenderable().get();
    renderer->addRenderableToList(cursor);
    cursorGridPos._x = 0;
    cursorGridPos._y = 0;
}

//Create towers
void Game::placeTower(Vector2 gridSlot){
    
    if(currency >= TOWER_PRICE && slotsGrid[gridSlot._x + (GRID_WIDTH*gridSlot._y) ] == 0){
        updateCurrency(-TOWER_PRICE);
        slotsGrid[gridSlot._x + (GRID_WIDTH*gridSlot._y) ] = 1;
        //Placeholder Spawner
        SDL_Texture *texture = renderer->createTexture("assets/tower01.png");

        GameObject *go = new GameObject("Tower", Vector2(CURSOR_INIT_POSITION_X + (gridSlot._x*MOVE_INTENSITY_X), CURSOR_INIT_POSITION_Y + (gridSlot._y*MOVE_INTENSITY_Y)), texture, Vector2(80,80), true, gridSlot);
        renderer->addRenderableToList(go->getRenderable().get());
        Tower *tower = new class Tower(go->getIndex());
        auto character = static_cast<Character*>(tower);
        go->addCharacter(std::shared_ptr<Character>(character));
        auto it = _towers.end();
        instance->_towers.emplace_back(tower);
        }
}


void Game::addBulletToList(Bullet *bullet){
    _bullets.emplace_back(bullet);
}
void Game::removeCharacterFromList(Character *character){
    
    Bullet* bullet = dynamic_cast<Bullet*> (character);
    if(bullet){
        for(int i =0; i<_bullets.size(); i++) if(_bullets[i] == bullet) _bullets.erase(_bullets.begin() + i);
    }
    Tower* tower = dynamic_cast<Tower*> (character);

    if(tower){
        for(int i =0; i<_towers.size(); i++) if(_towers[i] == tower) _towers.erase(_towers.begin() + i);
        
    }
    Enemy* enemy = dynamic_cast<Enemy*> (character);

    if(enemy){
        for(int i =0; i<_enemies.size(); i++) if(_enemies[i] == enemy) _enemies.erase(_enemies.begin() + i);
    }
    delete(character);
}

void Game::updateCurrency(int c){
    currency += c;
    UserInterface::updateTextValue("currency", std::to_string(currency));

}

void Game::cleanSlot(Vector2 slot){
    
    slotsGrid[slot._x + (GRID_WIDTH*slot._y) ] = 0;
}
void Game::setupUI(){
    
    //Resources (Upper bar)
    
    //Guide for commands (Lower bar)
}


