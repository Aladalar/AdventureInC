#include <iostream>
#include <string>
#include "core/constants.h"
#include "core/logger.h"
#include "core/gameObject.h"
#include "managers/screenManager.h"
#include "screens/gameScreen.h"
#include "raylib.h"

int main(int argc, char *argv[]){
    Logger::info("Starting application");

    GameObject GAME_OBJECT;

    
    InitWindow(Constants::SCREEN_WIDTH, Constants::SCREEN_HEIGHT, Constants::WINDOW_NAME);
    ToggleFullscreen();
    SetTargetFPS(60);
    
    Logger::info("Window initialized");
    
    ScreenManager* SCENE_MANAGER = GAME_OBJECT.getScreenManager();
    SCENE_MANAGER->changeScene("Test Scene 1");

    while (!WindowShouldClose()) {

        BeginDrawing();
        ClearBackground(DARKBLUE);        
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        Vector2 mousePos = GetMousePosition();
        GAME_OBJECT.handleClick(mousePos);
    }
        GAME_OBJECT.update();
        SCENE_MANAGER->update();
        SCENE_MANAGER->draw();

        EndDrawing();
    }
    
    CloseWindow();
    Logger::info("Application closed");

    return 0;
}