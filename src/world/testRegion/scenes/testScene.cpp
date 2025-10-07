#include "world/testRegion/scenes/testScene.h"
#include "utilities/logger.h"

void TestScene::load(){
    name = "test-scene";

    background = LoadTexture("assets/regions/test-region/test-scene/test-collision.png");
    navMap = LoadImage("assets/regions/test-region/test-scene/test-collision.png");

    if (background.id == 0) {
        Logger::error("Failed to load background for test-scene");
    }
    if (navMap.data == nullptr) {
        Logger::error("Failed to load navmap for test-scene");
    }
    
    Logger::info("TestScene loaded");

}

void TestScene::unload() {
    UnloadTexture(background);
    //UnloadTexture(foreground);
    UnloadImage(navMap);
    Logger::info("TestScene unloaded");
}

void TestScene::onEnter() {
    Logger::info("Entered TestScene");
}

void TestScene::onLeave() {
    Logger::info("Left TestScene");
}