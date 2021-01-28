//
//  Input.hpp
//  TiaG
//
//  Created by Ricardo Marginador on 27/01/21.
//

#ifndef Input_hpp
#define Input_hpp

#include <iostream>

class Input{
    public :
    Input();
    ~Input();
    enum inputKey {none, up, down, right, left};
    inputKey keyDown;
    static inputKey getKeyDown();
    static Input *instance;

};
#endif /* Input_hpp */
