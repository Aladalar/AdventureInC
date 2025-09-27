#ifndef NAVIGATION_H
#define NAVIGATION_H

#include "raylib.h"
#include <vector>

class Navigation {

    public:
        Navigation();
        void loadScene(Image newCollisionMap);
        std::vector<Vector2> findPath(Vector2 start, Vector2 goal);
        void setCurrentPath(const std::vector<Vector2>& path);
        

        void drawDebugGrid();
        void drawDebugPath(); 

    private:
        Image collisionMap;
        std::vector<Vector2> currentPath;
        static const int GRID_SIZE = 50;
        static const int GRID_WIDTH = 1920 / GRID_SIZE;
        static const int GRID_HEIGHT = 1080 / GRID_SIZE;
        bool pathGrid[GRID_WIDTH][GRID_HEIGHT];


};

#endif