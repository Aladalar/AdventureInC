#ifndef GAME_H
#define GAME_H

#include <string>
#include "raylib.h"
#include "utilities/logger.h"
#include "managers/screenManager.h"

class Game{

    public:
        Game();
        ~Game();

        void preInit();
        void initialize();
        void postInit();
        void run();
        void quit();
    
    private:
        // Screen settings
        Vector2 RESOLUTION = {1940, 1080};
        const char* WINDOW_NAME = "Adventure Game";
        int TARGET_FPS = 60;

        // Debug Tools
        bool debugMode = false;

        //TODO: * to Managers;
        ScreenManager screenManager;  
};

#endif