//
//  UserInterface.cpp
//  TiaG
//
//  Created by Ricardo Marginador on 10/02/21.
//

#include "UserInterface.hpp"


UserInterface::UserInterface(){
    
    
    
}

UserInterface::~UserInterface(){};
UIElement:: UIElement(int xpos, int ypos, string text, string font, SDL_Color& color) : labelText(text), labelFont(font), labelColor(color){
    std::cout << "UIElement Created "<< std::endl;
    _transform = new SDL_Rect();
    _transform->x = xpos;
    _transform->y = ypos;
    setText();
    Renderer::instance->addRenderableToList(std::move(this));
}

UIElement::~UIElement(){};

void UIElement::updateText(string text){
    labelText = text;
    setText();
}

void UIElement::setText(){
    std::cout << "UIElement SetText "<< std::endl;

    SDL_Surface* surf = TTF_RenderText_Blended(Assets::instance->getFont(labelFont),labelText.c_str(),labelColor);
    if(!(_texture = SDL_CreateTextureFromSurface(Renderer::instance->getRenderer(), surf))){
        std::cout << "Text rendering error" << std::endl;
    }
    SDL_FreeSurface(surf);
    
    SDL_QueryTexture(_texture, NULL, NULL, &_transform->w, &_transform->h);
    
}

