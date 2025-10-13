#include "managers/screenManager.h"
#include "utilities/logger.h"
#include "game.h"

ScreenManager::ScreenManager(){

    activeScene = nullptr;
    debugMode = false;
    menuVisible = false;
    dialogueVisible = false;
}

ScreenManager::~ScreenManager(){

}

void ScreenManager::init(Game* g){

    game = g;
    Logger::init("Screen manager initialized");
}

void ScreenManager::draw(){

    if(activeScene == nullptr){
        static bool logged = false;
        if(logged){
            Logger::error("Scene is still null cannot draw screen! [SCREENMANAGER]");
            logged = true;
        }
        return;
    }

    drawBackground();
   /* drawItems();
    drawPawns();
    drawDialogueBox();
    drawMenu();
    */
    if (game->getDebugMode()){
        drawDebug();
        DrawCircle(50, 400, 10, BLUE);
    }

}

void ScreenManager::drawDebug(){
    game->getNavigationManager()->debugDraw();
}

void ScreenManager::update(){
    
}

void ScreenManager::setScene(Scene* currentScene){
    activeScene = currentScene;
}


void ScreenManager::drawBackground(){
    DrawTextureV(activeScene->background, {0,0}, WHITE);
};

void drawFrontground();
void drawItems();
void drawPawns();
void drawUI();
void drawDialogueBox();
void drawMenu();
void drawTransitionOverlay();
void drawDebugOverlays();