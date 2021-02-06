//
//  Game.cpp
//  This Is a Game
//
//  Created by Ricardo Marginador on 25/01/21.
//

#include "Game.hpp"



Renderable *cursor;
Vector2 cursorGridPos;

Game::Game(){
    
}

Game::~Game(){
    
}

void Game::init(const char *title, int xpos, int ypos, int width, int height, bool fullscreen){
    int flags = fullscreen ? SDL_WINDOW_FULLSCREEN : 0;
    
    if(SDL_Init(SDL_INIT_EVERYTHING) == 0){
        std::cout<< "SDL Subsystens Initialized..."<< std::endl;
        //TODO: Remove New (Use shared_ptr instead of raw pointer)
        renderer = new Renderer();
        renderer->init(title, xpos, ypos, width, height, flags);
        //TODO: Remove New (Use unique_ptr instead of raw pointer)
        input = new Input();
        isRunning = true;
    }else{
        isRunning = false;
    }
    //Create cursor
    createGameGrid();
    createCursor();
    enemySpawner();

}

void Game::handleEvents(){
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

    GameObject *go = new GameObject("Tower", Vector2(CURSOR_INIT_POSITION_X + (gridSlot._x*MOVE_INTENSITY_X), CURSOR_INIT_POSITION_Y + (gridSlot._y*MOVE_INTENSITY_Y)), texture, Vector2(80,80), false);
    renderer->addRenderableToList(go->getRenderable());
}

//Create enemies
void Game::enemySpawner(){
    
    //Placeholder Spawner
    SDL_Texture *texture = renderer->createTexture("assets/pixelEnemy.png");

    GameObject *go = new GameObject("Enemy", Vector2(ENEMY_SPAWN_X, ENEMY_SPAWN_Y ), texture, Vector2(80,80), false);
    renderer->addRenderableToList(go->getRenderable());
}




void Game::enemyController(){
    //Iterate in the enemy list
    //Move all enemies one speed Unity to the left
    
}

void Game::setupUI(){
    
    //Resources (Upper bar)
    
    //Guide for commands (Lower bar)
}


