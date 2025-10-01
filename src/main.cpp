#include <iostream>
#include <string>
#include "core/constants.h"
#include "core/logger.h"
#include "screens/gameScreen.h"
#include "scene/test1Scene.h"
#include "scene/test2Scene.h"
#include "raylib.h"

int main(int argc, char *argv[]){
    Logger::info("Starting application");

    GameObject GAME_OBJECT;
    
    InitWindow(Constants::SCREEN_WIDTH, Constants::SCREEN_HEIGHT, Constants::WINDOW_NAME);
    ToggleFullscreen();
    SetTargetFPS(60);
    
    Logger::info("Window initialized");
    Test1Scene test;
    Test2Scene test2;

    GAME_OBJECT.loadScene(&test2);

    GameScreen screen(GAME_OBJECT);
    
    while (!WindowShouldClose()) {

        BeginDrawing();
        ClearBackground(DARKBLUE);        

        screen.update();
        screen.draw();

        EndDrawing();
    }
    
    CloseWindow();
    Logger::info("Application closed");

    return 0;
}