//
//  UserInterface.cpp
//  TiaG
//
//  Created by Ricardo Marginador on 10/02/21.
//

#include "UserInterface.hpp"

SDL_Color ACOLOR_WHITE {255,255,255,255};
SDL_Color ACOLOR_BLACK {0,0,0,255};
SDL_Color ACOLOR_BLUE {0,0,255,255};
SDL_Color ACOLOR_GREEN {0,255,0,255};
SDL_Color ACOLOR_RED {255,0,0,255};
int currency = 0;
UserInterface::UserInterface(){
    
    
    
}

void UserInterface::buildUI(){
    Assets::instance->addFont("arial", "fonts/arial.ttf", 50);

    //TopBar
    UIElement *currency = new UIElement(160, 60, "1000", "arial", ACOLOR_BLACK);
    uiElements.emplace("currency", currency);
    //LowerBar
    UIElement *commands = new UIElement(160, 800, "F", "arial", ACOLOR_BLACK);
    uiElements.emplace("cmd", commands);
}

void UserInterface::updateTextValue(string uIKey, string value)
{
    uiElements[uIKey]->updateText(value);
}

//Initialize map
UserInterface::UIMap UserInterface::uiElements = { {"x", nullptr}};
void UserInterface::updateData(){
    
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

