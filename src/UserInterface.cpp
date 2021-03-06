//
//  UserInterface.cpp
//  TiaG
//
//  Created by Ricardo Marginador on 10/02/21.
//

#include "UserInterface.hpp"


int currency = 0;
UserInterface::UserInterface(){
    
    
    
}

void UserInterface::gameOverScreen(){
    Assets::instance->addFont("big-Arial", "fonts/arial.ttf", 1000);

    UIElement *died = new UIElement(400, 360, "You Died", "arial", ACOLOR_RED);
    UIElement *gameover = new UIElement(400, 360 + 50, "Game Over", "arial", ACOLOR_RED);
    
    uiElements.emplace("died", died);
    uiElements.emplace("gameOver", gameover);

    
}
void UserInterface::buildUI(){
    Assets::instance->addFont("arial", "fonts/arial.ttf", 50);

    //TopBar
    UIElement *currency = new UIElement(170, 70, "1000", "arial", ACOLOR_BLACK);
    uiElements.emplace("currency", currency);
    //LowerBar
    UIElement *commands = new UIElement(160, 800, "F", "arial", ACOLOR_BLACK);
    uiElements.emplace("cmd", commands);
    Renderer::instance->createRenderable("assets/tower01.png", 80, 80, 65, 770);
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
UIElement:: UIElement(int xpos, int ypos, string text, string font, SDL_Color color) : labelText(text), labelFont(font), labelColor(color){
    _transform = new SDL_Rect();
    _transform->x = xpos;
    _transform->y = ypos;
    setText();
    Renderer::instance->addUIElementToList(std::shared_ptr<Renderable>(std::move(this)));
}

UIElement::~UIElement(){};

void UIElement::updateText(string text){
    labelText = text;
    setText();
}

void UIElement::setText(){

    SDL_Surface* surf = TTF_RenderText_Blended(Assets::instance->getFont(labelFont),labelText.c_str(),labelColor);
    if(!(_texture = SDL_CreateTextureFromSurface(Renderer::instance->getRenderer(), surf))){
    }
    SDL_FreeSurface(surf);
    
    SDL_QueryTexture(_texture, NULL, NULL, &_transform->w, &_transform->h);
    
}

