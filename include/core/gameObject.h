#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "game/player.h"
#include "game/mouseInput.h"
#include "game/navigation.h"
#include "scene/scene.h"

class GameObject {
private:
    Player player;
    MouseInput input;
    Navigation nav;
    
    Scene* currentScene;
    
public:
    GameObject();
    ~GameObject();
    
    // Scene management
    void loadScene(Scene* scene);
    void changeScene(const std::string& sceneName);
    
    // Getters for GameScreen to access
    Player& getPlayer() { return player; }
    MouseInput& getInput() { return input; }
    Navigation& getNavigation() { return nav; }
    Scene* getCurrentScene() { return currentScene; }
    
    // Game logic coordination
    void handleClick(Vector2 clickPos);
    void update();
};

#endif