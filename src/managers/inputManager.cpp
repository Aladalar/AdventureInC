#include "managers/inputManager.h"
#include "utilities/logger.h"
#include "game.h"

InputManager::InputManager() {
    
}

InputManager::~InputManager() {

    keyMacros.clear();
}


void InputManager::init(Game* g){

    game = g;
    setKeyMacros();
    Logger::init("Input manager was initialized.");
}

void InputManager::reload(){
    
    keyMacros.clear();
    setKeyMacros();
    Logger::init("Input manager was reloaded");
}

void InputManager::check(){

    for(const Key& key : keyMacros){
        if(IsKeyPressed(key.key_name)){
            key.action();
        }
    }
    mouseInput();
}

void InputManager::mouseInput(){

    if(IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)){
        Logger::info("Mouse right button was clicked");
        return;
    }
};
void InputManager::setKeyMacros(){

    keyMacros.push_back({KEY_F1, [this]() { toggleDebug(); }});

};

void InputManager::toggleDebug(){
    
    game->toggleDebug();
    Logger::info("F1 was pressed to toggle debug");
}