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
Character::~Character(){
    entity = nullptr;
    
}
Character::Character(GameObject *go, Character::CharacterType type){
    
    entity = go;
    
    //reset timers
    bulletTimer = std::chrono::milliseconds(_colldown);
    bulletLastSpawn = std::chrono::system_clock::now();
    charType = type;
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
    
    entity->addCharacter(this);
}
void Character::act(){
    //Check if this entity has collider
    if(!entity) return;
    Collider *thiscol = entity->getCollider();
    //Check if the collider have other collisor
    Collider *col = nullptr;
    if(thiscol){
        col = entity->getCollider()->isColliding();
        //if(col)
            //std::cout <<entity->getName() << " is colliding with :" << col->getGameObject()->getName()<<std::endl;
           // std::cout <<std::to_string(charType) << " is colliding with :" << col->getGameObject()->getChar()->charType<<std::endl;
            
    }
    int mult = 1;
    //Move
    //Only if no enemy collision is detected
    
    //Attack
    if(attackType == AttackType::Ranged){
        
        auto timeNow = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - bulletLastSpawn);
        if(bulletTimer<= timeNow){
            //Setup timer back
            std::chrono::milliseconds cycleTime = std::chrono::milliseconds(_colldown);
            bulletTimer = cycleTime + timeNow;
            bulletLastSpawn = std::chrono::system_clock::now();
            
       
        SDL_Texture *texture = Renderer::createTexture("assets/bullet.png");
        GameObject *go = new GameObject("Bullet", Vector2(entity->getRenderable()->_transform->x + entity->getRenderable()->_transform->w/2 + 30, entity->getRenderable()->_transform->y), texture, Vector2(60,60), true);
        Character *bullet = new Character(go, Character::CharacterType::Bullet);
        
        Game::instance->addBulletToList(bullet);
        Renderer::instance->addRenderableToList(go->getRenderable());
        }
    }else if(attackType == AttackType::Melle){
        if(col) {
            GameObject *target = col->getGameObject();
            if(!target) return;
            std::cout << charType << " : " <<Character::CharacterType::Bullet << std::endl;
            if(charType == Character::CharacterType::Bullet){
            

                if(target && target->getChar()->charType == Character::CharacterType::Enemy){
                    target->getCollider()->setCollision(nullptr);
                    target->getChar()->takeDamage(50);
                    
                   
                    die();
                    
                    return;
                    //If Target == tower and type == enemy
                    //If target == enemy && type == bullet
                }
            }
            if(charType == Character::CharacterType::Enemy){
                if(target != nullptr){
                    //std::cout<<"Collision with : " << target->getName()<<std::endl;
                   //if(target->getChar()->charType == Character::CharacterType::Tower)
                       mult = 0;
                    //If Target == tower and type == enemy
                    //If target == enemy && type == bullet
                }
            }
            
            
        }
    }
    if(entity)
        entity->getRenderable()->_transform->x += speed * mult;

}

int Character::takeDamage(int damage){
    std::cout << "The entity : " << entity->getName() << " took " << damage << " damage" << std::endl;
    health -= damage;
    if(health <=0) die();
    return health;
}

void Character::die(){
    Game::instance->removeBulletToList(this);
    delete(this->entity);
    
}




