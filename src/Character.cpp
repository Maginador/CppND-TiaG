//
//  Enemy.cpp
//  TiaG
//
//  Created by Ricardo Marginador on 06/02/21.
//

#include "Character.hpp"

Character::Character(){
    
}

Character::Character(GameObject *go, Character::CharacterType type){
    
    entity = go;
    //Set stats for each characterType (enemies and towers)
    //TODO: replace with scripting structure, maybe using external xml,txt or similar for stats
    if(type == Character::CharacterType::Enemy){
        health = 100;
        speed = -1;
    }
}
void Character::act(){
    //Move
    entity->getRenderable()->_transform->x += speed;
    //Attack
    //TODO: add collision detection to check if it is close to a tower
}

int Character::takeDamage(int damage){
    return health;
}




