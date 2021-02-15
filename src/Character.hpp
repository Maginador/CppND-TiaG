//
//  Enemy.hpp
//  TiaG
//
//  Created by Ricardo Marginador on 06/02/21.
//

#ifndef Character_hpp
#define Character_hpp

#include <stdio.h>
#include "GameObject.hpp"
#include "Game.hpp"

//Foward reference for circle header include
class Game;
class Collider;

class Character{
    public :
    enum CharacterType {Enemy, Tower, Bullet};
    enum AttackType {None, Melle, Ranged};
    Character();
    Character(GameObject *go);
    ~Character();
    virtual void preAct();
    virtual void act();
    int takeDamage(int damage);
    GameObject* getEntity(){return entity;}
    int getHealth() {return health;}
    protected :
    GameObject *entity;
    int health;
    int speed;
    int _colldown;
    int _lootCurrency;
    std::chrono::milliseconds bulletTimer;
    std::chrono::time_point<std::chrono::system_clock> bulletLastSpawn;
    AttackType attackType;
    void die();
    Collider *col;
    int mult = 0;
    
};

class Enemy : public Character{
    
    public :
    Enemy(GameObject *go);
    void act();

};

class Bullet : public Character{
    public :
    Bullet(GameObject *go);
    void act();

};

class Tower : public Character{
    public :
    Tower(GameObject *go);
    void act();

};
#endif /* Character_hpp */
