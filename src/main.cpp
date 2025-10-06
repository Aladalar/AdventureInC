#include <iostream>
#include <string>
#include "utilities/logger.h"
#include "raylib.h"

int main(int argc, char *argv[]){
    Logger::info("Starting application");
    
    InitWindow(1940,1080,"Adventure Game");
    SetTargetFPS(60);
    ToggleFullscreen();
    
    Logger::info("Window initialized");
    
  
    while (!WindowShouldClose()) {

        BeginDrawing();
        ClearBackground(DARKBLUE);        
       

        EndDrawing();
    }
    
    CloseWindow();
    Logger::info("Application closed");

    /*
    Game game;
    game.preInit();
    game.initialize();
    game.postInit();
    game.run();
    return 0;
    */
    return 0;
}