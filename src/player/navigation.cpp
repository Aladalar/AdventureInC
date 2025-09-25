#include <navigation.h>

Navigation::Navigation() {


    for (int x = 0; x < GRID_WIDTH; x++) {
        for (int y = 0; y < GRID_HEIGHT; y++) {
            pathGrid[x][y] = false;
        }
    }
}

void Navigation::loadScene(Image newCollisionMap){
    collisionMap = newCollisionMap;
    for (int x = 0; x < GRID_WIDTH; x++) {
        for (int y = 0; y < GRID_HEIGHT; y++) {
            int pixelX = x * GRID_SIZE + GRID_SIZE / 2;
            int pixelY = y * GRID_SIZE + GRID_SIZE / 2;
            pathGrid[x][y] = ColorIsEqual(GetImageColor(collisionMap, pixelX, pixelY), WHITE);
        }
    }
}

void Navigation::drawDebugGrid() {
    for (int x = 0; x < GRID_WIDTH; x++) {
        for (int y = 0; y < GRID_HEIGHT; y++) {
            int pixelX = x * GRID_SIZE + GRID_SIZE / 2;
            int pixelY = y * GRID_SIZE + GRID_SIZE / 2;
            
            Color dotColor = pathGrid[x][y] ? BLUE : RED; 
            DrawCircle(pixelX, pixelY, 3, dotColor);
        }
    }
}

void Navigation::setCurrentPath(const std::vector<Vector2>& path) {
    currentPath = path;
}

void Navigation::drawDebugPath(){
    if (currentPath.size() < 2) return;
    for(int i =0; i < currentPath.size() -1; i++){
       DrawLine(currentPath[i].x, currentPath[i].y, currentPath[i+1].x, currentPath[i+1].y, MAGENTA);
    }
    for (const Vector2& waypoint : currentPath) {
        DrawCircle(waypoint.x, waypoint.y, 5, GREEN);
    }
}

std::vector<Vector2> Navigation::findPath(Vector2 start, Vector2 goal){
    std::vector<Vector2> path;

    int startX = (int)start.x / GRID_SIZE;
    int startY = (int)start.y / GRID_SIZE;
    int goalX = (int)goal.x / GRID_SIZE;  
    int goalY = (int)goal.y / GRID_SIZE;

    // Your existing boundary and validity checks stay the same
    if (startX < 0 || startX >= GRID_WIDTH || startY < 0 || startY >= GRID_HEIGHT ||
        goalX < 0 || goalX >= GRID_WIDTH || goalY < 0 || goalY >= GRID_HEIGHT) {
        return path;  
    }
    if (!pathGrid[startX][startY] || !pathGrid[goalX][goalY]) {
        return path;
    }
    if (startX == goalX && startY == goalY) {
        path.push_back(goal);
        return path;
    }

    bool visited[GRID_WIDTH][GRID_HEIGHT] = {false};
    int parentX[GRID_WIDTH][GRID_HEIGHT], parentY[GRID_WIDTH][GRID_HEIGHT];
    
    // Queue for cells to explore
    std::vector<std::pair<int, int>> queue;
    queue.push_back({startX, startY});
    visited[startX][startY] = true;
    
    while (!queue.empty()) {
        auto current = queue[0];
        queue.erase(queue.begin());
        
        int currentX = current.first;
        int currentY = current.second;
        
        // Check all 8 neighbors
        for (int dx = -1; dx <= 1; dx++) {
            for (int dy = -1; dy <= 1; dy++) {
                if (dx == 0 && dy == 0) continue;
                
                int neighborX = currentX + dx;
                int neighborY = currentY + dy;
                
                if (neighborX >= 0 && neighborX < GRID_WIDTH && neighborY >= 0 && neighborY < GRID_HEIGHT &&
                    pathGrid[neighborX][neighborY] && !visited[neighborX][neighborY]) {
                    
                    visited[neighborX][neighborY] = true;
                    parentX[neighborX][neighborY] = currentX;
                    parentY[neighborX][neighborY] = currentY;
                    queue.push_back({neighborX, neighborY});
                    
                    if (neighborX == goalX && neighborY == goalY) {
                        // Reconstruct path
                        int px = goalX, py = goalY;
                        while (px != startX || py != startY) {
                            Vector2 waypoint = {(float)(px * GRID_SIZE + GRID_SIZE/2), (float)(py * GRID_SIZE + GRID_SIZE/2)};
                            path.insert(path.begin(), waypoint);
                            int newPx = parentX[px][py];
                            int newPy = parentY[px][py];
                            px = newPx;
                            py = newPy;
                        }
                        Vector2 startWaypoint = {(float)(startX * GRID_SIZE + GRID_SIZE/2), (float)(startY * GRID_SIZE + GRID_SIZE/2)};
                        path.insert(path.begin(), startWaypoint);
                        return path;
                    }
                }
            }
        }
    }
    
    return path; // No path found
}