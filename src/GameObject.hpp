//
//  GameObject.hpp
//  This Is a Game
//
//  Created by Ricardo Marginador on 25/01/21.
//

#ifndef GameObject_hpp
#define GameObject_hpp

#include <stdio.h>
#include "Physics.hpp"
#include "Renderer.hpp"
#include <memory>
#include <SDL2_image/SDL_image.h>
using std::unique_ptr;

struct Vector2{

    int _x;
    int _y;
    Vector2(){};
    Vector2(int x, int y);
    //Vector2& operator=(Vector2 &b);
    
};

class Transform{
    public :
    Transform(){};
    ~Transform(){};
    Transform(int x, int y);
    
    Transform(Vector2 pos);
    
    Vector2 _position;
};

class GameObject{
  
    public :
    GameObject(const char *name = "new GameObject", Vector2 initialPosition = Vector2 (0,0), const SDL_Texture *tex = nullptr, bool hasCollider = false );
    ~GameObject();
    std::string getName(){ return _name;}
    Collider* getCollider(){ return _collider.get();}
    Renderable* getRenderable(){ return _renderable.get();}
    void addCollider(); 
    void addRenderable();
    private :
    std::unique_ptr<Collider> _collider = nullptr;
    std::unique_ptr<Renderable> _renderable = nullptr;
    std::unique_ptr<Transform> _transform = nullptr;
    const char *_name;
};




#endif /* GameObject_hpp */
