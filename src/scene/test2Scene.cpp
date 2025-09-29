#include "scene/test2Scene.h"

void Test2Scene::loadScene() {
    sceneName = "Test Scene 2";
    playerSpawnPoint = {100, 400};
    
    navMap = LoadImage("assets/data/collision/test-collision-2.png");
    background = LoadTexture("assets/data/collision/test-collision-2.png");

    MapTransition transition;
    transition.position = {100, 400};
    transition.transitionHeight = 200;
    transition.targetScene = "test";
    transition.targetSpawnPoint = {50, 500};
    mapChangePoints.push_back(transition);
}

void Test2Scene::unloadScene() {
    UnloadImage(navMap);
}