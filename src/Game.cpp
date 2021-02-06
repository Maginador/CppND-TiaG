//
//  Game.cpp
//  This Is a Game
//
//  Created by Ricardo Marginador on 25/01/21.
//

#include "Game.hpp"

const int MOVE_INTENSITY_Y = 120;
const int CURSOR_INIT_POSITION_Y = 100;

const int MOVE_INTENSITY_X = 80;
const int CURSOR_INIT_POSITION_X = 50;


const int GRID_WIDTH = 10;
const int GRID_HEIGHT = 5;

Renderable *cursor;

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

}

void Game::handleEvents(){
    SDL_Event event;
    SDL_PollEvent(&event);
        if(event.type ==  SDL_QUIT)
            isRunning=false;
        else if(event.type == SDL_KEYDOWN){
            switch( event.key.keysym.sym ){
                case SDLK_UP:
                    input->keyDown = Input::inputKey::up;
                    break;

                    case SDLK_DOWN:
                    input->keyDown = Input::inputKey::down;
                    break;

                    case SDLK_LEFT:
                    input->keyDown = Input::inputKey::left;
                    break;

                    case SDLK_RIGHT:
                    input->keyDown = Input::inputKey::right;
                    break;

                    default:
                    input->keyDown = Input::inputKey::none;
                    break;
                }
        }
        else {
            input->keyDown = Input::inputKey::none;
    }
}

void Game::update(){
    renderer->render();
    
    
    //Move Cursor
    if(Input::getKeyDown() == Input::inputKey::down && cursor->_transform->y < CURSOR_INIT_POSITION_Y + MOVE_INTENSITY_Y * 4){
        cursor->_transform->y += MOVE_INTENSITY_Y;
    }
    else if(Input::getKeyDown() == Input::inputKey::up && cursor->_transform->y > CURSOR_INIT_POSITION_Y){
        cursor->_transform->y -= MOVE_INTENSITY_Y;
    }
    else if(Input::getKeyDown() == Input::inputKey::right && cursor->_transform->x < CURSOR_INIT_POSITION_X + MOVE_INTENSITY_X * 10){
        cursor->_transform->x += MOVE_INTENSITY_X;
    }
    else if(Input::getKeyDown() == Input::inputKey::left && cursor->_transform->x > CURSOR_INIT_POSITION_X){
        cursor->_transform->x -= MOVE_INTENSITY_X;
    }
}

bool Game::running(){
    return isRunning;
}

void Game::createGameGrid(){
    SDL_Texture *texture = renderer->createTexture("assets/slot_floor.png");
    //grid iteration
    for(int i =0; i<GRID_WIDTH; i++){
        for(int o =0; o<GRID_HEIGHT; o++){
            GameObject *go = new GameObject("Environment_Slot", Vector2(CURSOR_INIT_POSITION_X + (i*MOVE_INTENSITY_X), CURSOR_INIT_POSITION_Y + (o*MOVE_INTENSITY_Y)), texture, Vector2(80,80), false);
            renderer->addRenderableToList(go->getRenderable());
        }
    }

    
}

void Game::createCursor(){
    
    SDL_Texture *texture = renderer->createTexture("assets/cursor.png");

    GameObject *go = new GameObject("Cursor", Vector2(CURSOR_INIT_POSITION_X, CURSOR_INIT_POSITION_Y ), texture, Vector2(80,80), false);
    cursor = go->getRenderable();
    renderer->addRenderableToList(cursor);
}

//Create environment GameObjects
void CreateEnvironment(){
    
}

//Create towers
void CreateTower(){
    
}

//Create enemies
void CreateEnemies(){
    
}


