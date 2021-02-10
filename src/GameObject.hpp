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
#include "Character.hpp"
#include <memory>
#include <SDL2_image/SDL_image.h>
using std::unique_ptr;
//declaration for circle include 'GameObject/Collider'
class Collider;
class Character;

struct Vector2{

    int _x;
    int _y;
    Vector2(){_x =0; _y=0;};
    Vector2(int x, int y);
    Vector2& operator=(Vector2 &b);
    
};

class Transform{
    public :
    Transform(){};
    ~Transform(){};
    Transform(int x, int y);
    Transform(Vector2 pos);
    
    //Rule of five
    Transform& operator=(const Transform &cb);
    Transform(const Transform &cb);
    Transform& operator=(Transform &&cb);
    Transform(Transform &&cb );
    
    Vector2 *_position;
};

class GameObject{
  
    public :
    GameObject(const char *name, Vector2 initialPosition, SDL_Texture *tex, Vector2 size, bool hasCollider );
    ~GameObject();
    //Rule of five
    GameObject& operator=(const GameObject &cb);
    GameObject(const GameObject &cb);
    GameObject& operator=(GameObject &&cb);
    GameObject(GameObject &&cb );
    
    std::string getName(){ return _name;}
    Collider* getCollider(){ return _collider;}
    Renderable* getRenderable(){ return _renderable;}
    Character* getChar(){ return _character;}
    void addCollider(); 
    void addRenderable();
    void addCharacter(Character *character);
    private :
    Character *_character = nullptr;
    Collider *_collider = nullptr;
    Renderable *_renderable = nullptr;
    Transform *_transform = nullptr;
    const char *_name = nullptr;
};




#endif /* GameObject_hpp */
