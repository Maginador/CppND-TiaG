//
//  GameObject.cpp
//  This Is a Game
//
//  Created by Ricardo Marginador on 25/01/21.
//
#include "GameObject.hpp"
using std::unique_ptr;
using std::make_unique;
SDL_mutex* goMutex = SDL_CreateMutex();

vector<std::unique_ptr<GameObject>> GameObject::gameObjectsReferences;
GameObject* GameObject::getGameObject(int index){
   
    SDL_LockMutex(goMutex);
    //TODO: check why weird indexes come sometimes
    if(index > gameObjectsReferences.size() || index < 0) return nullptr;
    GameObject* obj = gameObjectsReferences[index].get();
    if(obj == NULL) return nullptr;
    SDL_UnlockMutex(goMutex);
    return obj;
    
}
void GameObject::clear(){
    
    
    Renderer::instance->addDeleteToSchedule(_renderable);
    
    
}
GameObject::GameObject(const char *name, Vector2 initialPosition, SDL_Texture *tex, Vector2 size, bool hasCollider , Vector2 slot){
    
    _slot = slot;
    globalIndex = (int)gameObjectsReferences.size();
    //GameObject
    _name = name;
    
    //Transform
    _transform = std::make_unique<Transform>(initialPosition);
    
    //Renderable
    if(tex != nullptr){
        _renderable = std::make_shared<Renderable>(tex, size._x, size._y, _transform->_position->_x, _transform->_position->_y);
    }
    //Collider
    if(hasCollider){
        _collider = std::make_shared<Collider>(globalIndex, _renderable->_transform);
    }
    
    gameObjectsReferences.emplace_back(this);
};

GameObject::~GameObject(){
    std::cout<<"GameObject destructor"<<std::endl;

};

std::shared_ptr<Renderable> GameObject::getRenderable(){
    return _renderable;
}
//Rule of five implementation
//Copy Constructor
GameObject::GameObject(const GameObject &b){
    
    _name = b._name;
    _character = b._character;
    _collider = std::move(b._collider);
    //_transform = std::make_unique<Transform>(b._transform);
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
    //_transform = std::make_unique<Transform>(b._transform);
    _renderable = b._renderable;

    return *this;
}

//Move Constructor
GameObject::GameObject(GameObject &&b){

    _name = b._name;
    _character = b._character;
    _collider = b._collider;
   // _transform = std::make_unique<Transform>(std::move(b._transform));
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
   // _transform = std::make_unique<Transform>(std::move(b._transform));
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

void GameObject::addCharacter(std::shared_ptr<Character> character){
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


