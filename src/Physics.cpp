//
//  Physics.cpp
//  This Is a Game
//
//  Created by Ricardo Marginador on 25/01/21.
//

#include "Physics.hpp"

//***Physics***
void Physics::simulate(){
    int collisionMatrix[_simulationColliders.size()] [_simulationColliders.size()];
    
    for(int i =0; i<_simulationColliders.size();i++){
        for(int o = 0; o<_simulationColliders.size();o++){
        //TODO: Calculate intersection between all colliders
        if(collisionMatrix[i][o] != 0){ continue;}
            
        else{
            //Calculate intersection between [i]x[o]
            Collider *aCol = _simulationColliders[i];
            Collider *bCol = _simulationColliders[o];
            
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
}

void Physics::includeBodyToSimulation(Collider *col){
    _simulationColliders.emplace_back(col);
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
    
    b.underCollision = nullptr;
    b.collisor = nullptr;
    b.boundingBox = NULL;
    b.gameObject = nullptr;

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
    
    b.underCollision = nullptr;
    b.collisor = nullptr;
    b.boundingBox = NULL;
    b.gameObject = nullptr;

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
Collider::Collider(GameObject *go, SDL_Rect *rect){
    gameObject = go;
    boundingBox = rect;
    collisor = nullptr;
}

Collider::~Collider(){};

Collider* Collider::isColliding(){
    if(collisor)
        return collisor;
    else
        return nullptr;
}

SDL_Rect* Collider::getRect(){
    return boundingBox;
}

GameObject* Collider::getGameObject(){
    return gameObject;
}
