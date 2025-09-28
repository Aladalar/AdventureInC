#include <iostream>
#include "core/constants.h"
#include "core/logger.h"
#include "game/player.h"
#include "game/mouseInput.h"
#include "game/navigation.h"
#include "screens/gameScreen.h"
#include "raylib.h"

int main(int argc, char *argv[]){
    Logger::info("Starting application");

    Player player;
    MouseInput input;
    Navigation nav;
    
    InitWindow(Constants::SCREEN_WIDTH, Constants::SCREEN_HEIGHT, Constants::WINDOW_NAME);
    SetTargetFPS(60);
    
    Logger::info("Window initialized");
    
    Image img = LoadImage("assets/data/collision/test-collision.png");
    Texture2D map = LoadTextureFromImage(img);
    
    nav.loadScene(img); 
    GameScreen screen(player, input, nav, map);
    
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