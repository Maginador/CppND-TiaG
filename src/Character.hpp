//
//  Enemy.hpp
//  TiaG
//
//  Created by Ricardo Marginador on 06/02/21.
//

#ifndef Character_hpp
#define Character_hpp

#include <stdio.h>
#include <SDL2/SDL.h>
#include "GameObject.hpp"
#include "Game.hpp"
#include "Time.hpp"
//Foward reference for circle header include
class Game;
class Collider;

class Character{
    public :
    Character();
    Character(int go);
    ~Character();
    virtual void preAct();
    virtual void act();
    int takeDamage(int damage);
    int getEntity(){return entity;}
    int getHealth() {return health;}
    protected :
    int entity;
    int health;
    int speed;
    int _colldown;
    Time *_colldownTimer;
    int _lootCurrency;
    void die();
    Collider *col;
    int moveMultiplier = 0;
    
};

class Enemy : public Character{
    
    public :
    Enemy(int go);
    void act();
    static int act(void* data);

};

class Bullet : public Character{
    public :
    Bullet(int go);
    void act();
    

};

class Tower : public Character{
    public :
    Tower(int go);
    void act();
    static int act(void* data);
    private :

};

class Factory : public Tower{
    public :
    Factory(int go);
    void act();
    static int act(void* data);
    private :
    
};
#endif /* Character_hpp */
