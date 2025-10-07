#ifndef SECOND_TEST_SCENE_H
#define SECOND_TEST_SCENE_H
#include "world/scene.h"

class SecondTestScene : public Scene {
public:
    void load() override;
    void unload() override;
    void onEnter() override;
    void onLeave() override;
};
#endif