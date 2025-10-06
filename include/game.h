#ifndef GAME_H
#define GAME_H

#include "raylib.h"

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

        bool debugMode = false;

        //TODO: * to Managers;  
};

#endif