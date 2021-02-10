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
    _transform = new Transform(initialPosition);
    
    //Renderable
    if(tex != nullptr){
        //TODO: Add Renderable
        _renderable = new Renderable(tex, size._x, size._y, _transform->_position->_x, _transform->_position->_y);
    }
    //Collider
    if(hasCollider){
        _collider = new Collider(this, _renderable->_transform);
    }
};

GameObject::~GameObject(){
    //TODO: Object Destruction
};

//Rule of five implementation
//Copy Constructor
GameObject::GameObject(const GameObject &b){
    
    _name = b._name;
    _character = b._character;
    _collider = std::move(b._collider);
    _transform = b._transform;
    _renderable = b._renderable;
}

//Copy Assingment
GameObject& GameObject::operator=(const GameObject &b){

    if(this == &b){
        return *this;
    }

    _name = b._name;
    _character = b._character;
    _collider = b._collider;
    _transform = b._transform;
    _renderable = b._renderable;

    return *this;
}

//Move Constructor
GameObject::GameObject(GameObject &&b){

    _name = b._name;
    _character = b._character;
    _collider = b._collider;
    _transform = b._transform;
    _renderable = b._renderable;
    
    b._name = nullptr;
    b._character = nullptr;
    b._collider = nullptr;
    b._transform = NULL;
    b._renderable = nullptr;

}

//Move Assignment
GameObject& GameObject::operator=(GameObject &&b){
 
    if(this == &b){
        return *this;
    }

    _name = b._name;
    _character = b._character;
    _collider = b._collider;
    _transform = b._transform;
    _renderable = b._renderable;
    
    b._name = nullptr;
    b._character = nullptr;
    b._collider = nullptr;
    b._transform = NULL;
    b._renderable = nullptr;

    return *this;
}

void GameObject::addCollider(){
    //TODO: a way to add collider on the fly
}

void GameObject::addRenderable(){
    //TODO: a way to add renderable on the fly
}

void GameObject::addCharacter(Character* character){
    _character = character;
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


