//
//  GameObject.cpp
//  This Is a Game
//
//  Created by Ricardo Marginador on 25/01/21.
//
#include "GameObject.hpp"
using std::unique_ptr;

GameObject::GameObject(const char *name, Vector2 initialPosition, const SDL_Texture *tex, bool hasCollider ){
    
    //GameObject
    _name = name;
    
    //Transform
    _transform->_position = initialPosition;
    
    //Renderable
    if(tex != nullptr){
        //TODO: Add Renderable
    }
    //Collider
    if(hasCollider){
        //TODO: Add Collider
    }
};

GameObject::~GameObject(){
    //TODO: Object Destruction
};


void GameObject::addCollider(){
    //TODO: a way to add collider on the fly
}

void GameObject::addRenderable(){
    //TODO: a way to add renderable on the fly
}


/*
Vector2& Vector2::operator=(Vector2 &b){
  
    this = b;
};


Transform::Transform(int x, int y){
    this();
    _position(x,y);
    
}

Transform::Transform(Vector2 pos){
    this();
    _position(pos);
}

*/
