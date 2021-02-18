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
#include "SDL2/SDL_image.h"
#include "SDL2.SDL.h" 
//declaration for circle include 'GameObject/Collider'
class GameObject;

class Collider{
    public :
    Collider(int gameObject, SDL_Rect *rect);
    ~Collider();
    
    //Rule of five
    Collider& operator=(const Collider &cb);
    Collider(const Collider &cb);
    Collider& operator=(Collider &&cb);
    Collider(Collider &&cb );
    
    bool hasCollisor(){return underCollision;}
    Collider* isColliding();
    void setCollision(Collider *col);
    int getGameObject();
    SDL_Rect* getRect();
    
    private:
    int gameObject = 0;
    SDL_Rect *boundingBox = nullptr;
    bool underCollision = false;
    Collider *collisor = nullptr;
};

class Physics{
    
public:
    Physics(){    if(instance == nullptr)
        instance = this;};
    ~Physics();
    static Physics *instance; 
    void simulate();
    void includeBodyToSimulation(Collider *col);
    void removeBodyToSimulations(Collider *col);
    private :
    std::vector<Collider*> _simulationColliders;
    bool calculateBoundingCollision(SDL_Rect *a, SDL_Rect *b);
};



#endif /* Physics_hpp */
