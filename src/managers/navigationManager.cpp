#include "managers/navigationManager.h"
#include "utilities/logger.h"
#include "game.h"
#include <algorithm>

NavigationManager::NavigationManager() {
    
    gridWidth = GetScreenWidth() / gridCellSize;
    gridHeight = GetScreenHeight() / gridCellSize;
};

NavigationManager::~NavigationManager() {
};

void NavigationManager::init(Game* g){
    game = g;
};

void NavigationManager::setScene(Image* newMap){
    navMap = newMap;
    grid.clear();
    if(navMap != nullptr){
        buildGrid();
        Logger::info("=== Grid Built ===");
        Logger::info("gridWidth: " + std::to_string(gridWidth));
        Logger::info("gridHeight: " + std::to_string(gridHeight));
        Logger::info("grid.size(): " + std::to_string(grid.size()));
        Logger::info("Expected: " + std::to_string(gridWidth * gridHeight));
        if (grid.size() > 0) {
            GridCell testCell = grid[16 * gridWidth + 2];
            Logger::info("Cell[2,16] walkable: " + std::string(testCell.walkable ? "YES" : "NO"));
        }
    } else {
        Logger::error("Cannot generate mapGrid, becouse map is missing| [NAVIGATION MANAGER]");
    }
   
       
};

bool NavigationManager::isWalkable(int x, int y){
    if (x < 0 || x >= navMap->width || y < 0 || y >= navMap->height) {
        return false;
    }
    if(GetImageColor(*navMap, x, y).r == 255){
        return true;
    }
    return false;
};

void NavigationManager::debugDraw(){
    for(GridCell g : grid){
        if (g.walkable){
            DrawCircleV(gridToPixel(g.x, g.y), 5, GREEN);
        } else {
            DrawCircleV(gridToPixel(g.x, g.y), 5, RED);
        }

    }
    if (!currentPath.empty()) {
        for (size_t i = 0; i < currentPath.size() - 1; i++) {
            DrawLineV(currentPath[i], currentPath[i+1], YELLOW);
        }
        
        // Draw waypoints
        for (Vector2 point : currentPath) {
            DrawCircleV(point, 8, ORANGE);
        }
    }
}

std::vector<Vector2> NavigationManager::findPath(Vector2 start, Vector2 end){

    currentPath.clear();
    //Converting to Cells 
    int startX, startY, endX, endY;
    pixelToGrid(start.x, start.y, startX, startY);
    pixelToGrid(end.x, end.y, endX, endY);

    Logger::info("Start cell: (" + std::to_string(startX) + "," + std::to_string(startY) + ")");
    Logger::info("End cell: (" + std::to_string(endX) + "," + std::to_string(endY) + ")");
    Logger::info("Start walkable: " + std::string(getCell(startX, startY).walkable ? "YES" : "NO"));
    Logger::info("End walkable: " + std::string(getCell(endX, endY).walkable ? "YES" : "NO"));
    
    //Declare vectors for cell discovery
    std::vector<PathNode*> openNodes;
    std::vector<PathNode*> closedNodes;
    PathNode* startNode = new PathNode{startX, startY, 0, 0, 0, nullptr};
    openNodes.push_back(startNode);
    
    while (!openNodes.empty())
    {
        // GET the best node from openList
        PathNode* current = findLowestFCost(openNodes);
        if(current->x == endX && current->y == endY){
            // Found goal! Trace back through parents
            std::vector<Vector2> path;
            PathNode* node = current;  // Start at goal
            while(node != nullptr){    // Go until start (parent is nullptr)
                Vector2 pixel = gridToPixel(node->x, node->y);
                path.push_back(pixel);
                node = node->parent;   // Move to parent
            }
            Logger::info("Path found! Length: " + std::to_string(path.size()));
            // Path is backwards (goal→start), reverse it
            std::reverse(path.begin(), path.end());
            currentPath = path;
            return path;
        }
        
        // Move current to closed list
        closedNodes.push_back(current);
        // Remove from open list
     
        // 3x3 grid around current, skip center
        for(int dx = -1; dx <= 1; dx++){
            for(int dy = -1; dy <= 1; dy++){
                if(dx == 0 && dy == 0) continue;  // Skip self (center)
                
                int nx = current->x + dx;
                int ny = current->y + dy;
                
                // Validate and add to openList
                if(nx >= 0 && nx < gridWidth && ny >= 0 && ny < gridHeight){
                    if (getCell(nx, ny).walkable){
                        bool isValid = true;
                        for(PathNode* node : closedNodes){
                            if(node->x == nx && node->y == ny){
                                isValid = false;
                                break;
                            }
                        }
                        if(isValid){
                            PathNode* neighbor = new PathNode{
                                nx, 
                                ny,
                                current->gCost + 1,
                                calculateHeuristic(nx, ny, endX, endY),
                                0,
                                current
                            };
                            neighbor->fCost = neighbor->gCost + neighbor->hCost;
                            openNodes.push_back(neighbor);
                        }
                    }
                }
            }
        }
        openNodes.erase(std::remove(openNodes.begin(), openNodes.end(), current), openNodes.end());
    }
    Logger::info("No path found from (" + std::to_string(startX) + "," + std::to_string(startY) + ") to (" + std::to_string(endX) + "," + std::to_string(endY) + ")");

    return {};
};

void NavigationManager::buildGrid(){

    int w = 0;
    for(int x = 0; x < GetScreenWidth(); x += gridCellSize){
        int h = 0; 
        for(int y = 0; y < GetScreenHeight(); y += gridCellSize){
            if(isWalkable(x+gridCellSize/2,y+gridCellSize/2)){
                grid.push_back({w, h, true});
            } else {
                grid.push_back({w, h, false});
            }
            h++;
        }
        w++;
    }

};


// Navigation A* helper methods 
int NavigationManager::calculateHeuristic(int x1, int y1, int x2, int y2){
    return abs(x1 - x2) + abs(y1-y2);
};

Vector2 NavigationManager::gridToPixel(int gridX, int gridY){
    return {(float)gridX*gridCellSize+gridCellSize/2, (float)gridY*gridCellSize+gridCellSize/2};
};

void NavigationManager::pixelToGrid(int pixelX, int pixelY, int& gridX, int& gridY){
    gridX = pixelX/gridCellSize;
    gridY = pixelY/gridCellSize;
};

NavigationManager::PathNode* NavigationManager::findLowestFCost(std::vector<PathNode*>& openList){
    
    PathNode* n = openList[0];
    for(PathNode* node: openList){
        if(n->fCost > node->fCost){
            n = node;
        }
    }
    return n;
};

NavigationManager::GridCell NavigationManager::getCell(int x, int y){
    return grid[y * gridWidth + x];    
}
