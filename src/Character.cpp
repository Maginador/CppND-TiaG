//
//  Enemy.cpp
//  TiaG
//
//  Created by Ricardo Marginador on 06/02/21.
//

#include "Character.hpp"



//TODO: add specialized classes for tower, bullet and enemy instead of enum selection
Character::Character(){
    
}

Character::Character(GameObject *go, Character::CharacterType type){
    
    entity = go;
    
    //reset timers
    bulletTimer = std::chrono::milliseconds(_colldown);
    bulletLastSpawn = std::chrono::system_clock::now();
                                                                            
    //Set stats for each characterType (enemies and towers)
    //TODO: replace with scripting structure, maybe using external xml,txt or similar for stats
    if(type == Character::CharacterType::Enemy){
        health = 100;
        speed = -1;
        attackType = AttackType::Melle;
    }else if(type == Character::CharacterType::Tower){
        health = 300;
        speed = 0;
        attackType = AttackType::Ranged;
        _colldown = 1000;
    }else if(type == Character::CharacterType::Bullet){
        health = 1;
        speed = 1;
        attackType = AttackType::Melle;
    }
}
void Character::act(){
    //Check if this entity has collider
    Collider *thiscol = entity->getCollider();
    //Check if the collider have other collisor
    Collider *col = nullptr;
    if(thiscol)
    col = entity->getCollider()->isColliding();
        
    //Move
    entity->getRenderable()->_transform->x += speed;
    //Attack
    if(attackType == AttackType::Ranged){
       
        auto timeNow = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - bulletLastSpawn);
        std::cout<< "Timer :" << bulletTimer.count() << " : Time Now : " << timeNow.count() << std::endl;
        if(bulletTimer<= timeNow){
            //Setup timer back
            std::chrono::milliseconds cycleTime = std::chrono::milliseconds(_colldown);
            bulletTimer = cycleTime + timeNow;
            bulletLastSpawn = std::chrono::system_clock::now();
            
       
        SDL_Texture *texture = Renderer::createTexture("assets/bullet.png");
        GameObject *go = new GameObject("Bullet", Vector2(entity->getRenderable()->_transform->x + entity->getRenderable()->_transform->w/2 + 30, entity->getRenderable()->_transform->y), texture, Vector2(60,60), false);
        Character *bullet = new Character(go, Character::CharacterType::Bullet);
        
        Game::instance->addBulletToList(bullet);
        Renderer::instance->addRenderableToList(go->getRenderable());
        }
    }else if(attackType == AttackType::Melle){
        if(col != nullptr) {
            GameObject *target = col->getGameObject();
            if(target != nullptr){
                std::cout<<"Collision with : " << target->getName()<<std::endl;
                //If Target == tower and type == enemy
                //If target == enemy && type == bullet
            }
        }
    }
}

int Character::takeDamage(int damage){
    health -= damage;
    return health;
}




