#include "managers/navigationManager.h"
#include "utilities/logger.h"
#include "game.h"
#include <algorithm>
#include <unordered_set>

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
    
    // ===== 1. DECLARE & INITIALIZE =====
    currentPath.clear();
    
    // Convert to grid coordinates
    int startX, startY, endX, endY;
    pixelToGrid(start.x, start.y, startX, startY);
    pixelToGrid(end.x, end.y, endX, endY);
    
    // Validate
    if(!getCell(startX, startY).walkable || !getCell(endX, endY).walkable){
        Logger::warn("Start or end not walkable");
        return {};
    }
    
    // Data structures
    std::vector<PathNode*> openList;
    std::unordered_set<int> closedSet;  // Hash: y*gridWidth+x
    std::unordered_set<int> openSet;
    
    // Create start node
    PathNode* startNode = new PathNode{startX, startY, 0, 0, 0, nullptr};
    startNode->hCost = calculateHeuristic(startX, startY, endX, endY);
    startNode->fCost = startNode->gCost + startNode->hCost;
    openList.push_back(startNode);
    openSet.insert(startY * gridWidth + startX);
    
    // ===== 2. SEARCH LOOP =====
    PathNode* goalNode = nullptr;
    int iterations = 0;
    const int MAX_ITERATIONS = 10000;
    
    while(!openList.empty() && iterations < MAX_ITERATIONS){
        iterations++;
        
        // Get node with lowest fCost
        PathNode* current = findLowestFCost(openList);
        
        // Check if goal
        if(current->x == endX && current->y == endY){
            goalNode = current;
            break;
        }
        
        // Move to closed
        int currentHash = current->y * gridWidth + current->x;
        closedSet.insert(currentHash);
        openSet.erase(currentHash);
        openList.erase(std::remove(openList.begin(), openList.end(), current), openList.end());
        
        // Explore neighbors (4-direction: up, down, left, right)
        int directions[4][2] = {{0,-1}, {0,1}, {-1,0}, {1,0}};
        
        for(int i = 0; i < 4; i++){
            int nx = current->x + directions[i][0];
            int ny = current->y + directions[i][1];
            int neighborHash = ny * gridWidth + nx;
            
            // Check bounds
            if(nx < 0 || nx >= gridWidth || ny < 0 || ny >= gridHeight) continue;
            
            // Check walkable
            if(!getCell(nx, ny).walkable) continue;
            
            // Check if in closed
            if(closedSet.find(neighborHash) != closedSet.end()) continue;
            
            // Calculate costs
            int newGCost = current->gCost + 1;
            
            // Check if already in open
            if(openSet.find(neighborHash) != openSet.end()){
                // Find existing node and update if better path
                for(PathNode* node : openList){
                    if(node->x == nx && node->y == ny){
                        if(newGCost < node->gCost){
                            node->gCost = newGCost;
                            node->fCost = node->gCost + node->hCost;
                            node->parent = current;
                        }
                        break;
                    }
                }
            } else {
                // Create new node
                PathNode* neighbor = new PathNode{
                    nx, ny,
                    newGCost,
                    calculateHeuristic(nx, ny, endX, endY),
                    0,
                    current
                };
                neighbor->fCost = neighbor->gCost + neighbor->hCost;
                openList.push_back(neighbor);
                openSet.insert(neighborHash);
            }
        }
    }
    
    if(iterations >= MAX_ITERATIONS){
        Logger::warn("Pathfinding timeout!");
    }
    
    // ===== 3. RECONSTRUCT PATH =====
    std::vector<Vector2> path;
    
    if(goalNode != nullptr){
        PathNode* node = goalNode;
        while(node != nullptr){
            Vector2 pixel = gridToPixel(node->x, node->y);
            path.push_back(pixel);
            node = node->parent;
        }
        std::reverse(path.begin(), path.end());
        currentPath = path;
        Logger::info("Path found! Length: " + std::to_string(path.size()));
    } else {
        Logger::info("No path found");
    }
    
    // ===== 4. CLEANUP =====
    for(PathNode* node : openList){
        delete node;
    }
    
    // Note: closedSet only has hashes, actual nodes are deleted above
    // goalNode is part of openList, already deleted
    
    // ===== 5. RETURN =====
    return path;
}

void NavigationManager::buildGrid(){
    gridWidth = GetScreenWidth() / gridCellSize;
    gridHeight = GetScreenHeight() / gridCellSize;
    
    for(int y = 0; y < gridHeight; y++){
        for(int x = 0; x < gridWidth; x++){
            int pixelX = x * gridCellSize + gridCellSize/2;
            int pixelY = y * gridCellSize + gridCellSize/2;
            
            if(isWalkable(pixelX, pixelY)){
                grid.push_back({x, y, true});
            } else {
                grid.push_back({x, y, false});
            }
        }
    }
}


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

void NavigationManager::clearPath() {
    currentPath.clear();
}