//
//  Physics.hpp
//  This Is a Game
//
//  Created by Ricardo Marginador on 25/01/21.
//

#ifndef Physics_hpp
#define Physics_hpp

#include <vector>
#include <stdio.h>
#include "GameObject.hpp"
#include <SDL2_image/SDL_image.h>
#include <SDL2/SDL.h>
class GameObject;

class Collider{
    public :
    Collider(GameObject *gameObject, SDL_Rect *rect);
    ~Collider();
    Collider* isColliding();
    void setCollision(Collider *col);
    GameObject* getGameObject();
    SDL_Rect* getRect();
    
    private:
    GameObject *transform;
    SDL_Rect *boundingBox;
    bool underCollision;
    Collider *collisor;
};

class Physics{
    
public:
    void simulate();
    void includeBodyToSimulation(Collider *col);
    
    private :
    std::vector<Collider*> _simulationColliders;
    bool calculateBoundingCollision(SDL_Rect *a, SDL_Rect *b);
};



#endif /* Physics_hpp */
