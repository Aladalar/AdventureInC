#include <iostream>
#include <logger.h>
#include <player.h>
#include <mouseInput.h>
#include <navigation.h>
#include "raylib.h"

int main(int argc, char *argv[]){
    Logger::info("Starting application");
    
    InitWindow(1920, 1080, "Adventure Test");
    SetTargetFPS(60);
    
    Logger::info("Window initialized");
    
    Player player;
    MouseInput input;
    Navigation nav;
    Image img = LoadImage("assets/data/collision/test-collision.png");
    if (img.data == NULL) {
        Logger::error("Failed to load collision image");
    } else {
        Logger::info("Collision image loaded successfully");
    }

    Texture2D map = LoadTextureFromImage(img);
    if (map.id == 0) {
        Logger::error("Failed to create texture from image");
    } else {
        Logger::info("Texture created successfully - ID: " + std::to_string(map.id));
    }
    
    nav.loadScene(img);
    UnloadImage(img);

    
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(DARKBLUE);        

        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
            Vector2 clickPos = input.GetValidPosition(GetMousePosition());
            if (clickPos.x != -1) {
                std::vector<Vector2> path = nav.findPath(player.getCurrentPosition(), clickPos);
                if (!path.empty()) {
                    player.setPath(path);  // Use new waypoint system
                }
            }
        }
        DrawTexture(map, 0, 0, WHITE);
        player.updatePosition();
        player.draw();
        
        nav.drawDebugGrid();

        EndDrawing();
    }
    
    CloseWindow();
    Logger::info("Application closed");

    return 0;
}