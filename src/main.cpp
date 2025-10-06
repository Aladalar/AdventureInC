#include <iostream>
#include <string>
#include "game.h"

int main(int argc, char *argv[]){
    
    Game game;
    game.preInit();
    game.initialize();
    game.postInit();
    game.run();
    game.quit();

    return 0;
}