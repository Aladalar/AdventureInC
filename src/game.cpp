#include "game.h"


Game::Game(){

}

Game::~Game(){

}

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

    Logger::info("--- POST-INIT END ---");
}

void Game::run(){

    Logger::info("--- GAME STARTED ---");
    ToggleFullscreen();
    while (!WindowShouldClose()) {

        BeginDrawing();
        ClearBackground(DARKBLUE);        
       

        EndDrawing();
    }
}

void Game::quit(){
    Logger::info("--- ENDING OF APP ---");

    CloseWindow();
    
    Logger::info("Application closed");

}