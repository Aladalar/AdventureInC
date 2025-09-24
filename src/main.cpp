#include <iostream>
#include <logger.h>
#include <player.h>
#include <mouseInput.h>
#include "raylib.h"

int main(int argc, char *argv[]){
    Logger::info("Starting application");
    
    InitWindow(800, 600, "Adventure Test");
    
    Logger::info("Window initialized");
    
    Player player;
    MouseInput input;
    
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(DARKBLUE);

        DrawRectangle(0, 400, 800, 200, WHITE);
        

        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
            player.setTargetPosition(input.GetValidPosition(GetMousePosition()));
        }
        player.updatePosition();
        player.draw();

        EndDrawing();
    }
    
    CloseWindow();
    Logger::info("Application closed");
    
    return 0;
}