#include <iostream>
#include <logger.h>
#include <player.h>
#include "raylib.h"

int main(int argc, char *argv[]){
    Logger::info("Starting application");
    
    InitWindow(800, 600, "Adventure Test");
    
    Logger::info("Window initialized");
    
    Player player;
    
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(DARKBLUE);

        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
            player.setTargetPosition(GetMousePosition());
        }
        player.updatePosition();
        player.draw();

        EndDrawing();
    }
    
    CloseWindow();
    Logger::info("Application closed");
    
    return 0;
}