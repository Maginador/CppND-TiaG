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

class Character{
    public :
    enum CharacterType {Enemy, Tower, Bullet};
    enum AttackType {None, Melle, Ranged};
    Character();
    Character(GameObject *go, CharacterType);
    ~Character();
    void act();
    int takeDamage(int damage);
    GameObject* getEntity(){return entity;}
    int getHealth() {return health;}
    private :
    GameObject *entity;
    int health;
    int speed;
    int _colldown;
    std::chrono::milliseconds bulletTimer;
    std::chrono::time_point<std::chrono::system_clock> bulletLastSpawn;
    AttackType attackType;
    //TODO: Replace all type related stuff with subclasses for each type
    CharacterType charType;

    void die();
    
    
};
#endif /* Character_hpp */
