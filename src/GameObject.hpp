//
//  GameObject.hpp
//  This Is a Game
//
//  Created by Ricardo Marginador on 25/01/21.
//

#ifndef GameObject_hpp
#define GameObject_hpp

#include <stdio.h>
#include <vector>
#include "Physics.hpp"
#include "Renderer.hpp"
#include "Character.hpp"
#include <memory>
#include "SDL2/SDL_image.h"
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
    GameObject(const char *name, Vector2 initialPosition, SDL_Texture *tex, Vector2 size, bool hasCollider , Vector2 slot);
    ~GameObject();
    //Rule of five
    GameObject& operator=(const GameObject &cb);
    GameObject(const GameObject &cb);
    GameObject& operator=(GameObject &&cb);
    GameObject(GameObject &&cb );
    Vector2 getSlot() { return _slot;};
    int getIndex(){ return globalIndex;}
    static GameObject* getGameObject(int index);
    std::string getName(){ return _name;}
    std::shared_ptr<Collider> getCollider(){ return _collider;}
    std::shared_ptr<Renderable> getRenderable();
    std::shared_ptr<Character> getChar(){return _character;}
    void addCollider(); 
    void addRenderable();
    void addCharacter(std::shared_ptr<Character> character);
    private :
    int globalIndex;
    
    std::shared_ptr<Character> _character = nullptr;
    std::shared_ptr<Collider> _collider = nullptr;
    std::shared_ptr<Renderable> _renderable = nullptr;
    std::unique_ptr<Transform> _transform = nullptr;
    const char *_name = nullptr;
    Vector2 _slot;
    static std::vector<std::unique_ptr<GameObject>> gameObjectsReferences;
};




#endif /* GameObject_hpp */
