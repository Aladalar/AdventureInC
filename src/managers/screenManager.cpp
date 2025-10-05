#include "core/gameObject.h"
#include "managers/screenManager.h"
#include "scene/test1Scene.h"
#include "scene/test2Scene.h"
#include "core/logger.h"
#include <string>

ScreenManager::ScreenManager(GameObject& go): gameObject(go){
    gameRender = new GameScreen(gameObject);
    //menuRender = new Screen();
    //cinemaRender = new Screen();
    currentScene = nullptr;  // This one stays nullptr until scene loads


    loadMaps();
    screenType = ScreenType::GAME;
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
    Logger::info("Searching for scene: " + sceneName);
    for(Scene* scene : mapList){
        Logger::info("Checking: " + scene->getName());
        if(scene->getName() == sceneName){
            if(currentScene != nullptr){
                currentScene->unloadScene();
            }
            currentScene = scene;
            Logger::info("Scene assigned, calling loadScene");
            currentScene->loadScene();
            Logger::info("Scene loaded successfully");
             gameObject.getNavigation().loadScene(currentScene->getNavMap());
            gameObject.getPlayer().spawnPosition(currentScene->getSpawnPoint());
           
            break;
        }
    }
    if(currentScene == nullptr) {
        Logger::error("Scene not found: " + sceneName);
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

void ScreenManager::draw() {
    // Always draw game
    gameRender->draw();
    
    // Draw overlay based on screen type
    if (screenType == ScreenType::MENU) {
        menuRender->draw();
    } else if (screenType == ScreenType::CINEMA) {
        cinemaRender->draw();
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