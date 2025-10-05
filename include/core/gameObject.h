#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "game/player.h"
#include "game/mouseInput.h"
#include "game/navigation.h"
#include "scene/scene.h"

class ScreenManager;

class GameObject {
private:
    Player player;
    MouseInput input;
    Navigation nav;
    ScreenManager* screenManager;
    
public:
    GameObject();
    ~GameObject();

    // Getters for GameScreen to access
    Player& getPlayer() { return player; }
    MouseInput& getInput() { return input; }
    Navigation& getNavigation() { return nav; }

    // Game logic coordination
    void handleClick(Vector2 clickPos);
    void update();

    // Getters
    ScreenManager* getScreenManager(){return screenManager; };
};

#endif