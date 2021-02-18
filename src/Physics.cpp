//
//  Physics.cpp
//  This Is a Game
//
//  Created by Ricardo Marginador on 25/01/21.
//

#include "Physics.hpp"

SDL_mutex* physicsMutex = SDL_CreateMutex();
//***Physics***
Physics* Physics::instance = 0;

Physics::~Physics(){
    //TODO: Review 
}

void Physics::simulate(){
    int collisionMatrix[_simulationColliders.size()] [_simulationColliders.size()];
    SDL_LockMutex(physicsMutex);
    //initialize colision matrix
    for ( int v = 0; v<_simulationColliders.size(); v++ ){
        for ( int e = 0; e<_simulationColliders.size(); e++ ){
            collisionMatrix[v][e] = 0;}}
    
    for(int i =0; i<_simulationColliders.size();i++){
        for(int o = 0; o<_simulationColliders.size();o++){
        //TODO: Calculate intersection between all colliders
        if(collisionMatrix[i][o] != 0){ continue;}
            
        else{
            //Calculate intersection between [i]x[o]
            Collider *aCol = _simulationColliders[i];
            Collider *bCol = _simulationColliders[o];
            
            if(!aCol){
               _simulationColliders.erase(_simulationColliders.begin()+i);
                continue;
            }
            if(!bCol){
               _simulationColliders.erase(_simulationColliders.begin()+o);
                continue;
            }
            if(aCol == bCol) continue;
            //Calculate
            if(calculateBoundingCollision(aCol->getRect(), bCol->getRect())){
                //Insert collision if collision is true
                aCol->setCollision(bCol);
                bCol->setCollision(aCol);}
        }
        //Set this element as already visited in the list, this means we can stop calculating it
            collisionMatrix[i][o]=1;
        }
    }
    SDL_UnlockMutex(physicsMutex);
}

void Physics::includeBodyToSimulation(Collider *col){
    SDL_LockMutex(physicsMutex);
    _simulationColliders.emplace_back(col);
    SDL_UnlockMutex(physicsMutex);
}

void Physics::removeBodyToSimulations(Collider *col){
    SDL_LockMutex(physicsMutex);
    if (col != NULL){
    for(int i =0; i<_simulationColliders.size(); i++) if(_simulationColliders[i] == col) _simulationColliders.erase(_simulationColliders.begin() + i);
    }
    SDL_UnlockMutex(physicsMutex);
}

bool Physics::calculateBoundingCollision(SDL_Rect *a, SDL_Rect *b){
    //The sides of the rectangles
        int leftA, leftB;
        int rightA, rightB;
        int topA, topB;
        int bottomA, bottomB;

        //Calculate the sides of rect A
        leftA = a->x;
        rightA = a->x + a->w;
        topA = a->y;
        bottomA = a->y + a->h;

        //Calculate the sides of rect B
        leftB = b->x;
        rightB = b->x + b->w;
        topB = b->y;
        bottomB = b->y + b->h;
    
    
    //If any of the sides from A are outside of B
    if( bottomA <= topB )
    {
        return false;
    }

    if( topA >= bottomB )
    {
        return false;
    }

    if( rightA <= leftB )
    {
        return false;
    }

    if( leftA >= rightB )
    {
        return false;
    }
    //if no condition attended, we have a collision
    return true;
}

//***Collider***

//Rule of five implementation

Collider::~Collider(){
    Physics::instance->removeBodyToSimulations(this);
    boundingBox = nullptr;
    if(gameObject)
    gameObject = 0;
    collisor = nullptr; 
    underCollision = false;
    
}
//Copy Constructor
Collider::Collider(const Collider &b){
    
    gameObject = b.gameObject;
    boundingBox = b.boundingBox;
    collisor = b.collisor;
    underCollision = b.underCollision;
    
}

//Copy Assingment
Collider& Collider::operator=(const Collider &b){

    if(this == &b){
        return *this;
    }

    gameObject = b.gameObject;
    boundingBox = b.boundingBox;
    collisor = b.collisor;
    underCollision = b.underCollision;

    return *this;
}

//Move Constructor
Collider::Collider(Collider &&b){

    gameObject = b.gameObject;
    boundingBox = b.boundingBox;
    collisor = b.collisor;
    underCollision = b.underCollision;
    
    b.underCollision = false;
    b.collisor = nullptr;
    b.boundingBox = NULL;
    b.gameObject = 0;

}
//Move Assignment
Collider& Collider::operator=(Collider &&b){
 
    if(this == &b){
        return *this;
    }

    gameObject = b.gameObject;
    boundingBox = b.boundingBox;
    collisor = b.collisor;
    underCollision = b.underCollision;
    
    b.underCollision = false;
    b.collisor = nullptr;
    b.boundingBox = NULL;
    b.gameObject = 0;

    return *this;
}
void Collider::setCollision(Collider *col){
    if(col == nullptr){
        underCollision = false;
        collisor = nullptr;
    }else{
    underCollision = true;
    collisor = col;
    }

}
Collider::Collider(int go, SDL_Rect *rect){
    gameObject = go;
    boundingBox = rect;
    collisor = nullptr;
    Physics::instance->includeBodyToSimulation(this);
}


Collider* Collider::isColliding(){
    return collisor;
}

SDL_Rect* Collider::getRect(){
    return boundingBox;
}

int Collider::getGameObject(){
    return gameObject;
}
