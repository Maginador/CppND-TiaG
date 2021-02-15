//
//  UserInterface.hpp
//  TiaG
//
//  Created by Ricardo Marginador on 10/02/21.
//

#ifndef UserInterface_hpp
#define UserInterface_hpp

#include <stdio.h>
#include <iostream>
#include <SDL2_ttf/SDL_ttf.h>
#include <SDL2/SDL.h>
#include "Renderer.hpp"
#include "Assets.hpp"

using std::string;

class UserInterface{
    
public:
    UserInterface();
    ~UserInterface();
    void draw();
    void clear();
    void updateData();
};


class UIElement : public Renderable {
    
    public :
    UIElement(int xpos, int ypos, string text, string font, SDL_Color& color);
    ~UIElement();
    void setText();
    void updateText(string text);
    void move(SDL_Rect newPos);
    
    SDL_Rect* getRect(){ return _transform;}
    SDL_Texture* getTexture(){return _texture;}
    private :
    string labelText;
    string labelFont;
    SDL_Color labelColor;
    
};
#endif /* UserInterface_hpp */
