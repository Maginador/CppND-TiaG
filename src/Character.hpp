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

class Character{
    public :
    enum CharacterType {Enemy, Tower};
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
    void die();
    
    
};
#endif /* Character_hpp */
