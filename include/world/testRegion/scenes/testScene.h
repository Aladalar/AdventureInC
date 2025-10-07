#ifndef TEST_SCENE_H
#define TEST_SCENE_H
#include "world/scene.h"

class TestScene : public Scene {
public:
    void load() override;
    void unload() override;
    void onEnter() override;
    void onLeave() override;
};
#endif