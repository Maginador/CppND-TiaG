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
    _transform = std::make_unique<Transform>(initialPosition);
    
    //Renderable
    if(tex != nullptr){
        //TODO: Add Renderable
        _renderable = std::make_unique<Renderable>(tex, size._x, size._y, _transform->_position->_x, _transform->_position->_y);
    }
    //Collider
    if(hasCollider){
        _collider = std::make_unique<Collider>(this, _renderable->_transform);
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
  
    
    _x = b._x;
    _y = b._y;
    return *this;
}


Transform::Transform(int x, int y){
    _position = new Vector2(x,y);
    
}

Transform::Transform(Vector2 pos){
    _position = new Vector2(pos);
}


