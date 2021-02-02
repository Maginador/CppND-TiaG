//
//  Input.cpp
//  TiaG
//
//  Created by Ricardo Marginador on 27/01/21.
//

#include "Input.hpp"

Input* Input::instance = 0;
Input::Input(){
    if(instance == nullptr)
        instance = this;
};
Input::~Input(){};
Input::inputKey Input::getKeyDown(){
    if(instance != nullptr)
        return instance->keyDown;
    else
        return Input::inputKey::none;
}
