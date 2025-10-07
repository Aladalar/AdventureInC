#include "world/testRegion/scenes/secondTestScene.h"
#include "utilities/logger.h"

void SecondTestScene::load(){
    name = "second-test-scene";

    background = LoadTexture("assets/regions/test-region/test-scene/test-collision.png");
    navMap = LoadImage("assets/regions/test-region/test-scene/test-collision.png");

    if (background.id == 0) {
        Logger::error("Failed to load background for second-test-scene");
    }
    if (navMap.data == nullptr) {
        Logger::error("Failed to load navmap for second-test-scene");
    }
    
    Logger::info("SeconTestScene loaded");

}

void SecondTestScene::unload() {
    UnloadTexture(background);
    //UnloadTexture(foreground);
    UnloadImage(navMap);
    Logger::info("SeconTestScene unloaded");
}

void SecondTestScene::onEnter() {
    Logger::info("Entered SeconTestScene");
}

void SecondTestScene::onLeave() {
    Logger::info("Left SeconTestScene");
}