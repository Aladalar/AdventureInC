#ifndef SCENE_H
#define SCENE_H

#include "raylib.h"
#include <string>
#include <vector>

class Scene
{
    public:
        virtual ~Scene() = default;

        virtual void loadScene() = 0;
        virtual void unloadScene() = 0;
        
        struct MapTransition {
            Vector2 position;
            int transitionHeight;
            std::string targetScene;
            Vector2 targetSpawnPoint;
        };
        
        // Common getters
        const Image& getNavMap() { return navMap; }
        const Texture2D& getBackground() { return background; }
        const Texture2D& getForeground() { return foreground; }
        Vector2 getSpawnPoint() { return playerSpawnPoint; }
        const std::string& getName() { return sceneName; }
        std::vector<MapTransition> getMapTranstitions(){return mapChangePoints; }
        
        protected:
        std::string sceneName;
        Vector2 playerSpawnPoint;
        std::vector<MapTransition> mapChangePoints;
        
        Image navMap;
        Texture2D background;
        Texture2D foreground;
};

#endif