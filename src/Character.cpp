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
static SDL_mutex* characterLock = SDL_CreateMutex();


//TODO: add specialized classes for tower, bullet and enemy instead of enum selection
Character::Character(){}
Character::~Character(){
    entity = -1;
    col = nullptr;
    
}
Character::Character(int go){
    entity = go;
}

void Character::preAct(){
    //Check if this entity has collider
    if(entity<0) return;
    Collider *thiscol = GameObject::getGameObject(entity)->getCollider();
    //Check if the collider have other collisor
    col = nullptr;
    if(thiscol){
        col = GameObject::getGameObject(entity)->getCollider()->isColliding();
    }
    moveMultiplier = 1;
}
void Character::act(){
    //Move
    //Only if no enemy collision is detected
    SDL_LockMutex( Renderer::instance->rendererMtx );
    if(entity>=0)
        GameObject::getGameObject(entity)->getRenderable()->_transform->x += speed * moveMultiplier;
    SDL_UnlockMutex( Renderer::instance->rendererMtx );
    if(health <=0) die();
    
}

int Character::takeDamage(int damage){
    health -= damage;
    std::cout << "Character took  ." << damage << ".  damage. There is : ."  << health << ". left" << std::endl;
    return health;
}

void Character::die(){
    std::cout << "Character died " << std::endl;
    Game::instance->removeCharacterFromList(this);
    Game::instance->updateCurrency(_lootCurrency);
    
    if(col){
    if(col->hasCollisor()){ auto c = col ->isColliding(); if(c)c->setCollision(nullptr);}
        col->setCollision(nullptr);
    }delete(GameObject::getGameObject(entity));
    
    entity = -1;

}

//Enemy
Enemy::Enemy(int go) : Character(go){
    health = ENEMY_HEALTH;
    speed = -1;
    _lootCurrency = ENEMY_LOOT;

}

int Enemy::act(void* data){
    Enemy *enemy = (Enemy *)data;
    enemy->act();
    return 0;
}
void Enemy::act(){
    SDL_LockMutex( characterLock );
    Character::preAct();
    if(col) {
        GameObject *target = GameObject::getGameObject(col->getGameObject());
        if(!target || !target->getChar()) {
            SDL_UnlockMutex( characterLock );
            return;
}
        auto tower = dynamic_cast<class Tower *>(target->getChar());
        if(tower){
            moveMultiplier = 0;
            tower->takeDamage(10);
        }
    }
    Character::act();
    SDL_UnlockMutex( characterLock );
}

//Towers
Tower::Tower(int go) : Character(go){
    health = 300;
    speed = 0;
    _colldown = TOWER_COOLDOWN;
    _lootCurrency=0;
    _colldownTimer = new Time(_colldown, true);

}
void Tower::act(){
    Character::preAct();
    if(_colldownTimer->timedAction()){
        SDL_LockMutex( Renderer::instance->rendererMtx );
        SDL_Texture *texture = Renderer::createTexture("assets/bullet.png");
        GameObject *go = new GameObject("Bullet", Vector2(GameObject::getGameObject(entity)->getRenderable()->_transform->x + GameObject::getGameObject(entity)->getRenderable()->_transform->w/2 + 30, GameObject::getGameObject(entity)->getRenderable()->_transform->y), texture, Vector2(60,60), true);
            auto *bullet = new class Bullet(go->getIndex());
        
        Game::instance->addBulletToList(bullet);
        Renderer::instance->addRenderableToList(go->getRenderable());
        SDL_UnlockMutex( Renderer::instance->rendererMtx );
    }
    Character::act();
    SDL_UnlockMutex( characterLock );
}

int Tower::act(void* data){
    
    auto *tower = (Tower *)data;
    if(tower && tower->entity != -1)
         tower->act();
    
    
    return 0;
}

//Factory
Factory::Factory(int go) : Tower(go){
    health = 1;
    speed = 0;
    _colldown = FACTORY_COOLDOWN;
    _lootCurrency = FACTORY_INCOME;
    _colldownTimer = new Time(_colldown, true);

}
void Factory::act(){
    Character::preAct();
    if(_colldownTimer->timedAction()){
        Game::instance->updateCurrency(_lootCurrency);

    }
    Character::act();
    SDL_UnlockMutex( characterLock );
}

int Factory::act(void* data){
    
    auto *factory = (Factory *)data;
    if(factory && factory->entity != -1)
        factory->act();
    
    
    return 0;
}


//Bullet
Bullet::Bullet(int go) : Character(go){
    
    health = 1;
    speed = 1;
    _lootCurrency=0;
}
void Bullet::act(){
    Character::preAct();
    SDL_LockMutex( characterLock );
    if(col) {
        GameObject *target = GameObject::getGameObject(col->getGameObject());
        if(!target || target == GameObject::getGameObject(entity)) return;
        auto enemy = dynamic_cast<class Enemy *>(target->getChar());
        if(enemy){
            target->getCollider()->setCollision(nullptr);
            enemy->takeDamage(50);
            this->takeDamage(99999);
        }
    }
    Character::act();
}




