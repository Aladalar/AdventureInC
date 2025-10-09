#include "game.h"
#include "world/region.h"
#include "world/scene.h"
#include "world/testRegion/testRegion.h"

Game::Game(){

}

Game::~Game(){

}

void Game::loadRegion(Region* region){
    
    if (loadedRegions.find(region->getName()) != loadedRegions.end()){
        return;
    }

    loadedRegions[region->getName()] = region;
    region->load();
}

void Game::unloadRegion(Region* region){

    auto it = loadedRegions.find(region->getName());
    if (it != loadedRegions.end()) {
        it->second->unload(); 
        loadedRegions.erase(it);
    }
}

void Game::setScene(std::string regionName, std::string sceneName){

    auto reg = loadedRegions.find(regionName);
    if ( reg == loadedRegions.end()){
        Logger::error("Scene " + sceneName + " dont have loaded region " + regionName + " [GAME-SETSCENE]");
        return;
    }

    Scene* scene = reg->second->getScene(sceneName);

    if (scene == nullptr){
        Logger::error("Scene " + sceneName + " doesnt exist in region " + regionName + "[GAME-SETSCENE]");
        return;
    }
    
    if (currentScene != nullptr){
        // START ON EXIT ANIMATIONTS ETC
        currentScene->onLeave();
    }
    
    // SWAPING SCENE 
    currentScene = scene;
    currentScene->onEnter();
    
    // CONTINUE RENDER AS USUAL
    screenManager.setScene(currentScene);

}


/* App Init functions*/

void Game::preInit(){
    Logger::info("Starting application");

    InitWindow(RESOLUTION.x,RESOLUTION.y, WINDOW_NAME);
    SetTargetFPS(TARGET_FPS);

    Logger::info("--- PRE INIT DONE ---");
}

void Game::initialize(){
    Logger::info("--- INIT START ---");

    screenManager.init();

    Logger::info("--- INIT DONE ---");
}

void Game::postInit(){
    Logger::info("--- POST-INIT START ---");

    Region* tr = new TestRegion();
    loadRegion(tr);
    setScene("test-region", "test-scene");

    Logger::info("--- POST-INIT END ---");
}

void Game::run(){

    Logger::info("--- GAME STARTED ---");
    ToggleFullscreen();
    while (!WindowShouldClose()) {

        BeginDrawing();
        ClearBackground(DARKBLUE);        
       
        screenManager.draw();
        
        EndDrawing();
    }
}

void Game::quit(){
    Logger::info("--- ENDING OF APP ---");

    CloseWindow();
    
    Logger::info("Application closed");

}