#include "managers/screenManager.h"
#include <string>

ScreenManager::ScreenManager(){

}

ScreenManager::~ScreenManager(){

}

void ScreenManager::changeScene(const std::string& sceneName){
    for(Scene* scene : mapList){
        if(scene->getName() == sceneName){
            if(currentScene != nullptr){
                currentScene->unloadScene();
            };
            currentScene = scene;
            currentScene->loadScene();
            break;
        }
    }
}