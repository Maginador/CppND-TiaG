//
//  Input.hpp
//  TiaG
//
//  Created by Ricardo Marginador on 27/01/21.
//

#ifndef Input_hpp
#define Input_hpp

#include <iostream>
#include "SDL2/SDL.h" 

class Input{
    public :
    Input();
    ~Input();
    enum inputKey {none, up, down, right, left, f, space, q, e, esc};
    inputKey keyDown;
    static inputKey getKeyDown();
    static Input *instance;
    void handleEvents();
};
#endif /* Input_hpp */
