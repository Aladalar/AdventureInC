#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include "utilities/logger.h"
#include "raylib.h"
#include <vector>
#include <functional>

class Game;
class InputManager {
public:
    InputManager();
    ~InputManager();

    void init(Game* game);
    void reload();
    void check(); // main check loop - called in Game::run();
private:    
    void mouseInput();
    void setKeyMacros();

    Game* game;
    struct Key
    {
        KeyboardKey key_name;
        std::function<void()> action;
        //add like this keyMacros.push_back({KEY_F1, [this]() { toggleDebug(); }});
    };
    std::vector<Key> keyMacros;
    
    void toggleDebug();

};

#endif
