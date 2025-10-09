#include "world/testRegion/testRegion.h"
#include "world/testRegion/scenes/testScene.h"
#include "world/testRegion/scenes/secondTestScene.h"
#include "utilities/logger.h"

TestRegion::TestRegion() {
    name = "test-region";
}

void TestRegion::load() {

    Scene* s1 = new TestScene();
    Scene* s2 = new SecondTestScene();

    sceneList.push_back(s1);
    sceneList.push_back(s2);

    s1->load();
    s2->load();

    Logger::info("TestRegion loaded with " + std::to_string(sceneList.size()) + " scenes");
}

void TestRegion::unload() {

    for (Scene* scene : sceneList) {
        scene->unload();
        delete scene;
    }
    sceneList.clear();
    
    Logger::info("TestRegion unloaded");
}

Scene* TestRegion::getScene(std::string name){
    for(Scene* scene : sceneList){
        if (scene->getName() == name){
            return scene;
        }
    }
    return nullptr;
}