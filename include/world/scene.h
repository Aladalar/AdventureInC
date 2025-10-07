#ifndef SCENE_H
#define SCENE_H

#include <string>
#include "raylib.h"

class Scene{

    protected:
        std::string name;
        /*
            TODO Animations and other scene specific resources
        */

    public:
        Image navMap;
        Texture background;
        Texture foreground;
        std::string getName() {return name;};

        virtual void load() = 0;
        virtual void unload() = 0;

        virtual void onEnter() = 0;
        virtual void onLeave() = 0;

        /*
            TODO Animation hangle etc...
        */

};

#endif