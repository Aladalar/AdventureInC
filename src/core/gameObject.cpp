#include "core/gameObject.h"
#include "managers/screenManager.h"
#include "core/logger.h"


GameObject::GameObject(){
    screenManager = new ScreenManager(*this);
}

GameObject::~GameObject(){
    delete screenManager;
}

void GameObject::update(){
    player.updatePosition();
}

void GameObject::handleClick(Vector2 clickPos){
   Logger::info("Click at: " + std::to_string((int)clickPos.x) + "," + std::to_string((int)clickPos.y));

Scene* currentScene = screenManager->getCurrentScene();
if (currentScene == nullptr) {
    Logger::error("No scene loaded");
    return;
}

Vector2 validPos = input.GetValidPosition(clickPos, currentScene->getNavMap());
Logger::info("Valid pos: " + std::to_string((int)validPos.x) + "," + std::to_string((int)validPos.y));

if (validPos.x != -1) {
    Logger::info("Finding path");
    std::vector<Vector2> path = nav.findPath(player.getCurrentPosition(), clickPos);
    Logger::info("Path size: " + std::to_string(path.size()));
    if (!path.empty()) {
        nav.setCurrentPath(path);
        player.setPath(path);
        Logger::info("Path set");
    }
}


};