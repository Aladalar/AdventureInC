#include <iostream>
#include "logger.h"
#include "raylib.h"

int main(int argc, char *argv[]){
    Logger::info("Starting application");
    
    InitWindow(800, 600, "Adventure Test");
    
    Logger::info("Window initialized");
    
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(DARKBLUE);
        DrawText("Hello Raylib!", 10, 10, 20, WHITE);
        EndDrawing();
    }
    
    CloseWindow();
    Logger::info("Application closed");
    
    return 0;
}