#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include "utilities/logger.h"
#include "raylib.h"
#include <vector>
#include <functional>

class InputManager {
public:
    InputManager();
    ~InputManager();

    void check(); // main check loop - called in Game::run();
private:    
    void mouseInput();
    void keyboardInput();
    void setKeyMacros();

    struct Key
    {
        KeyboardKey key_name;
        std::function<void()> action;
        //add like this keyMacros.push_back({KEY_F1, [this]() { toggleDebug(); }});
    };
    std::vector<Key> keyMacros;
    
    /*
        TODO add macros functions
    */
};

#endif
