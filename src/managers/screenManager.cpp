#include "managers/screenManager.h"
#include "scene/test1Scene.h"
#include "scene/test2Scene.h"
#include <string>

ScreenManager::ScreenManager(GameObject& go): gameObject(go){
    gameRender = new GameScreen(gameObject);
    //menuRender = new Screen();
    //cinemaRender = new Screen();
    currentScene = nullptr;  // This one stays nullptr until scene loads


    loadMaps();
    screenType = ScreenType::CINEMA;
    isPaused = false;
}

ScreenManager::~ScreenManager(){

    delete cinemaRender;
    delete menuRender;
    delete gameRender;
    for(Scene* s : mapList){
        delete s;
    }
}

void ScreenManager::loadMaps(){
    mapList.push_back(new Test1Scene());
    mapList.push_back(new Test2Scene());
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

void ScreenManager::changeScreen(ScreenType type){
    screenType = type;
    if (type != ScreenType::GAME){
        isPaused = true;
    } else {
        isPaused = false;
    }
}

void ScreenManager::update() {
    if (isPaused) {
        // Update menu or cinema screen
        if (screenType == ScreenType::MENU) {
            menuRender->update();
        } else if (screenType == ScreenType::CINEMA) {
            cinemaRender->update();
        }
    } else {
        // Normal game routine
        gameRender->update();
    }
}

void ScreenManager::openMenu() {
    changeScreen(ScreenType::MENU);
}

void ScreenManager::closeMenu() {
    changeScreen(ScreenType::GAME);
}

void ScreenManager::playCinematic() {
    changeScreen(ScreenType::CINEMA);
}

void ScreenManager::stopCinematic() {
    changeScreen(ScreenType::GAME);
}