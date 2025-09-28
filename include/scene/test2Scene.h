#ifndef TEST2SCENE_H
#define TEST2SCENE_H

#include "scene.h"

class Test2Scene : public Scene {
public:
    void loadScene() override;
    void unloadScene() override;
};

#endif