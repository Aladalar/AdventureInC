#ifndef TEST1SCENE_H
#define TEST1SCENE_H

#include "scene.h"

class Test1Scene : public Scene {
public:
    Test1Scene();
    void loadScene() override;
    void unloadScene() override;
};

#endif