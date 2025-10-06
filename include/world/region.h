#ifndef REGION_H
#define REGION_H

#include <vector>
#include <string>
#include "world/scene.h"

class Region{

    private:
        std::string name;
        std::vector<Scene*> sceneList;
    public:
        virtual void load() = 0;
        virtual void unload() = 0;
        Scene* getScene(std::string name);
        std::string getName(){return name;};

        //TODO add more region specific resources
};

#endif