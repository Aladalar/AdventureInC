#include "managers/navigationManager.h"
#include "utilities/logger.h"

NavigationManager::NavigationManager() {
    
    gridWidth = GetScreenWidth() / gridCellSize;
    gridHeight = GetScreenHeight() / gridCellSize;
};

NavigationManager::~NavigationManager() {
};

void NavigationManager::init(){

    grid.clear();
    if(navMap != nullptr){
        buildGrid();
    } else {
        Logger::error("Cannot generate mapGrid, becouse map is missing| [NAVIGATION MANAGER]");
    }

};
void NavigationManager::setScene(Image* newMap){
    navMap = newMap;
};

bool NavigationManager::isWalkable(int x, int y){
    if(GetImageColor(*navMap, x, y).r == 255){
        return true;
    }
    return false;
};

std::vector<Vector2> NavigationManager::findPath(Vector2 start, Vector2 end){

    //Converting to Cells 
    int startX, startY, endX, endY;
    pixelToGrid(start.x, start.y, startX, startY);
    pixelToGrid(end.x, end.y, endX, endY);

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
            // Path is backwards (goal→start), reverse it
            std::reverse(path.begin(), path.end());
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
    return {};
};

void NavigationManager::buildGrid(){

    int w = 0;
    int h = 0; 
    for(int x = 0; x < GetScreenWidth(); x += gridCellSize){
        for(int y = 0; y < GetScreenHeight(); y += gridCellSize){
            if(isWalkable(x,y)){
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