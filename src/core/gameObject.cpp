#include "core/gameObject.h"

GameObject::GameObject(){
    currentScene = nullptr;
}

GameObject::~GameObject(){
    if (currentScene != nullptr){
        currentScene->unloadScene();
    }
}

void GameObject::loadScene(Scene* scene){

    if (currentScene != nullptr){
        currentScene->unloadScene();
    }
    currentScene = scene;
    currentScene->loadScene();

    nav.loadScene(currentScene->getNavMap());
    player.spawnPosition(currentScene->getSpawnPoint());    
}

void GameObject::changeScene(const std::string& sceneName){
    //TODO
};

void GameObject::handleClick(Vector2 clickPos){

    Vector2 validPos = input.GetValidPosition(clickPos, currentScene->getNavMap());
    if (validPos.x != -1) {
        std::vector<Vector2> path = nav.findPath(player.getCurrentPosition(), clickPos);
        if (!path.empty()) {
            nav.setCurrentPath(path);
            player.setPath(path);
        }
    }

};