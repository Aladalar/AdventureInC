#ifndef GAMESCREEN_H
#define GAMESCREEN_H

#include "screens/screen.h"
#include "raylib.h"
#include <vector>

class GameObject;
class GameScreen : public Screen {
private:
    GameObject& gameObject;

public:
    GameScreen(GameObject& gameObject);
    ~GameScreen();

    void drawDebugTransitions(const std::vector<Scene::MapTransition>& transitions);

    void update() override;
    void draw() override;
    void onEnter() override;
    void onExit() override;
};

#endif