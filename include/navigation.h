#include "raylib.h"
#include <vector>

class Navigation {

    public:
        Navigation();
        void loadScene(Image newCollisionMap);
        void drawDebugGrid();
        std::vector<Vector2> findPath(Vector2 start, Vector2 goal);

    private:
        Image collisionMap;
        static const int GRID_SIZE = 50;
        static const int GRID_WIDTH = 1920 / GRID_SIZE;
        static const int GRID_HEIGHT = 1080 / GRID_SIZE;
        bool pathGrid[GRID_WIDTH][GRID_HEIGHT];


};