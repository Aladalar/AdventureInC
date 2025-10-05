#include "scene/test1Scene.h"

Test1Scene::Test1Scene(){
    sceneName = "Test Scene 1";
}

void Test1Scene::loadScene() {
    playerSpawnPoint = {100, 400};
    
    navMap = LoadImage("assets/data/collision/test-collision.png");
    background = LoadTexture("assets/data/collision/test-collision.png");

    MapTransition transition;
    transition.position = {1800, 500};
    transition.transitionHeight = 200;
    transition.targetScene = "test2";
    transition.targetSpawnPoint = {50, 500};
    mapChangePoints.push_back(transition);
}

void Test1Scene::unloadScene() {
    UnloadImage(navMap);
}