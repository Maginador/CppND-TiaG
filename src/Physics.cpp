//
//  Physics.cpp
//  This Is a Game
//
//  Created by Ricardo Marginador on 25/01/21.
//

#include "Physics.hpp"


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
    transform = go;
    boundingBox = rect;
    
}

Collider::~Collider(){};

Collider* Collider::isColliding(){
    return collisor;
}

bool Physics::calculateBoundingCollision(SDL_Rect *a, SDL_Rect *b){
    
    return true;
}
SDL_Rect* Collider::getRect(){
    return boundingBox;
}

GameObject* Collider::getGameObject(){
    return transform;
}
