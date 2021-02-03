//
//  GameObject.cpp
//  This Is a Game
//
//  Created by Ricardo Marginador on 25/01/21.
//
#include "GameObject.hpp"
using std::unique_ptr;
using std::make_unique;

GameObject::GameObject(const char *name, Vector2 initialPosition, SDL_Texture *tex, Vector2 size, bool hasCollider ){
    
    //GameObject
    _name = name;
    
    //Transform
    _transform->_position = initialPosition;
    
    //Renderable
    if(tex != nullptr){
        //TODO: Add Renderable
        _renderable = make_unique<Renderable>(Renderable(tex, size._x, size._y, 0, 0));
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


Vector2::Vector2(int x, int y){
    _x = x;
    _y = y;
    
}

Vector2& Vector2::operator=(Vector2 &b){
  
    this->_x = b._x;
    this->_y = b._y;
    return *this;
}


Transform::Transform(int x, int y){
    this->_position._x = x;
    this->_position._y = y;

    
}
/*
Transform::Transform(Vector2 pos){
    this();
    _position(pos);
}

*/
