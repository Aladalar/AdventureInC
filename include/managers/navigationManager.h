#ifndef NAVIGATIONMANAGER_H
#define NAVIGATIONMANAGER_H

#include "raylib.h"
#include <vector>

class NavigationManager {
public:
    NavigationManager();
    ~NavigationManager();

    void init();
    void setScene(Image* newMap);
    
    bool isWalkable(int x, int y);
    std::vector<Vector2> findPath(Vector2 start, Vector2 end);

private:

    struct GridCell {
        int x, y;
        bool walkable;
    };
    
    struct PathNode {
        int x, y;           // Grid position
        int gCost;          // Distance from start
        int hCost;          // Heuristic to goal
        int fCost;          // g + h
        PathNode* parent;   // For path reconstruction
    };
    
    void buildGrid();
    int calculateHeuristic(int x1, int y1, int x2, int y2);
    Vector2 gridToPixel(int gridX, int gridY);
    void pixelToGrid(int pixelX, int pixelY, int& gridX, int& gridY);
    PathNode* findLowestFCost(std::vector<PathNode*>& openList);
    GridCell getCell (int x, int y);
    
    int gridCellSize = 100;
    int gridWidth;
    int gridHeight;
    std::vector<GridCell> grid;
    Image* navMap;
};

#endif