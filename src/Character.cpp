//
//  Enemy.cpp
//  TiaG
//
//  Created by Ricardo Marginador on 06/02/21.
//

#include "Character.hpp"
class Bullet;
class Tower;
class Enemy;


//TODO: add specialized classes for tower, bullet and enemy instead of enum selection
Character::Character(){}
Character::~Character(){
    entity = nullptr;
    
}
Character::Character(GameObject *go){
    entity = go;
    //reset timers
    
    entity->addCharacter(this);
}

void Character::preAct(){
    //Check if this entity has collider
    if(!entity) return;
    Collider *thiscol = entity->getCollider();
    //Check if the collider have other collisor
    col = nullptr;
    if(thiscol){
        col = entity->getCollider()->isColliding();
    }
    moveMultiplier = 1;
}
void Character::act(){
    //Move
    //Only if no enemy collision is detected
    if(entity)
        entity->getRenderable()->_transform->x += speed * moveMultiplier;
}

int Character::takeDamage(int damage){
    std::cout << "The entity : " << entity->getName() << " took " << damage << " damage" << std::endl;
    health -= damage;
    if(health <=0) die();
    return health;
}

void Character::die(){
    Game::instance->removeCharacterFromList(this);
    Game::instance->updateCurrency(_lootCurrency);
    delete(this->entity);
    
}

//Enemy
Enemy::Enemy(GameObject *go) : Character(go){
    health = 100;
    speed = -1;
    _lootCurrency=100;
    if(!_colldownTimer) _colldownTimer = new Time(std::chrono::milliseconds(3000), true);

}

int Enemy::act(void* data){
    Enemy *enemy = (Enemy *)data;
    enemy->act();
    return 0;
}
void Enemy::act(){
    Character::preAct();
    if(col) {
        GameObject *target = col->getGameObject();
        if(!target) return;
        auto tower = dynamic_cast<class Tower *>(target->getChar());
        if(tower){
            moveMultiplier = 0;
            if(_colldownTimer->timedAction()){
                tower->takeDamage(10);
            }
        }
    }
    Character::act();
}

//Towers
Tower::Tower(GameObject *go) : Character(go){
    health = 300;
    speed = 0;
    _colldown = 1000;
    _lootCurrency=0;
    if(!_colldownTimer) _colldownTimer = new Time(std::chrono::milliseconds(10000), true);

}
void Tower::act(){
    Character::preAct();
    if(_colldownTimer->timedAction()){
        SDL_Texture *texture = Renderer::createTexture("assets/bullet.png");
        GameObject *go = new GameObject("Bullet", Vector2(entity->getRenderable()->_transform->x + entity->getRenderable()->_transform->w/2 + 30, entity->getRenderable()->_transform->y), texture, Vector2(60,60), true);
            auto *bullet = new class Bullet(go);
        
        Game::instance->addBulletToList(bullet);
        Renderer::instance->addRenderableToList(go->getRenderable());
        Character::act();
        return;
    }
   
    
}

int Tower::act(void* data){
    
    auto *tower = (Tower *)data;
    std::cout << "Tower act thread" << std::endl;
    tower->act();
    
    
    return 0;
}

//Bullet
Bullet::Bullet(GameObject *go) : Character(go){
    
    health = 1;
    speed = 1;
    _lootCurrency=0;
}
void Bullet::act(){
    Character::preAct();
    if(col) {
        GameObject *target = col->getGameObject();
        if(!target || target == entity) return;
        auto enemy = dynamic_cast<class Enemy *>(target->getChar());
        if(enemy){
            target->getCollider()->setCollision(nullptr);
            enemy->takeDamage(50);
            die();
            return;
        }
    }
    Character::act();
}




