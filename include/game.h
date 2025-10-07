#ifndef GAME_H
#define GAME_H

#include <string>
#include <map>
#include "raylib.h"
#include "utilities/logger.h"
#include "managers/screenManager.h"
#include "world/region.h"
#include "world/scene.h"

class Game{

    public:
        Game();
        ~Game();

        void preInit();
        void initialize();
        void postInit();
        void run();
        void quit();

        void loadRegion(Region* region);
        void unloadRegion(Region* region);
        void setScene(std::string regionName, std::string sceneName);
    
    private:
        // Screen settings
        Vector2 RESOLUTION = {1940, 1080};
        const char* WINDOW_NAME = "Adventure Game";
        int TARGET_FPS = 60;

        // Debug Tools
        bool debugMode = false;

        //TODO: * to Managers;
        ScreenManager screenManager;  

        //Game-Screen var
        Scene* currentScene;
        std::map<std::string, Region*> loadedRegions;
};

#endif