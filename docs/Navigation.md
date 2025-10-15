# Navigation System

## Purpose
Handle pathfinding and movement navigation. Calculate optimal routes from start to goal positions while avoiding obstacles.

## Overview
Uses A* pathfinding algorithm on a grid-based system derived from scene navMaps. Supports 8-direction movement with diagonal blocking to prevent corner cutting.

---

## Components

### Navigation Grid
**Grid Structure:**
- Divides screen into cells (default: 25x25 pixels)
- Grid dimensions: `gridWidth × gridHeight`
- Stored as 1D vector with row-major ordering: `index = y * gridWidth + x`

**GridCell:**
```cpp
struct GridCell {
    int x, y;        // Grid coordinates
    bool walkable;   // Can pathfind through this cell
}
```

**Grid Building:**
- Loads from Scene's navMap (Image with RGB channels)
- Red channel (R=255) indicates walkable areas
- Samples pixel at center of each grid cell
- Converts walkable pixels to grid cells

---

## Pathfinding (A* Algorithm)

### PathNode Structure
```cpp
struct PathNode {
    int x, y;           // Grid coordinates
    int gCost;          // Distance from start (actual cost)
    int hCost;          // Heuristic to goal (estimated cost)
    int fCost;          // Total cost (g + h)
    PathNode* parent;   // Previous node in path
}
```

### Algorithm Flow
1. **Initialize:**
   - Convert start/goal from pixels to grid coordinates
   - Validate both positions are walkable
   - Create openList, closedSet, openSet
   - Add start node to openList

2. **Search Loop:**
   - Get node with lowest fCost from openList
   - If goal reached, reconstruct path and return
   - Move current node to closedSet
   - Explore all 8 neighbors:
     - Check bounds, walkable, not in closed
     - For diagonals: verify no corner cutting
     - Calculate costs (diagonal=14, straight=10)
     - Add to openList or update if better path found

3. **Reconstruct Path:**
   - Trace back through parent pointers
   - Convert grid coordinates to pixel positions
   - Reverse path (was goal→start, need start→goal)
   - Store in currentPath

4. **Cleanup:**
   - Delete all allocated PathNodes
   - Return path vector

### Movement Directions
**8-Direction Movement:**
```
Cardinal directions (cost: 10):
- North:  {0, -1}
- South:  {0, 1}
- West:   {-1, 0}
- East:   {1, 0}

Diagonal directions (cost: 14):
- NorthWest: {-1, -1}
- NorthEast: {1, -1}
- SouthWest: {-1, 1}
- SouthEast: {1, 1}
```

**Diagonal Blocking:**
- Before moving diagonally, check both adjacent cardinal cells
- Example: To move NE, both N and E cells must be walkable
- Prevents cutting through corners of obstacles

### Heuristic
**Manhattan Distance** (currently):
```cpp
h = abs(currentX - goalX) + abs(currentY - goalY)
```
Works well for grid-based movement. Could use Euclidean for more accuracy with diagonals.

---

## Data Structures

### Collections Used
- `std::vector<PathNode*> openList` - Nodes to explore
- `std::unordered_set<int> closedSet` - Already explored (stores hash: y*width+x)
- `std::unordered_set<int> openSet` - Tracks what's in openList for fast lookup
- `std::vector<Vector2> currentPath` - Final calculated path in pixels

### Why These Structures?
- **unordered_set for closed/open tracking:** O(1) lookup vs O(n) vector search
- **vector for openList:** Need to iterate to find lowest fCost (could optimize with priority_queue)
- **Hash function:** `y * gridWidth + x` uniquely identifies each cell

---

## Public Methods

### Core Functions
```cpp
void init(Game* g)
```
Initialize with Game reference
```cpp
void setScene(Image* navMap)
```
Load new scene's navigation map, rebuild grid
```cpp
std::vector<Vector2> findPath(Vector2 start, Vector2 goal)
```
Calculate path from start to goal, returns waypoints in pixels
```cpp
void clearPath()
```
Clear current path (called on scene change)
```cpp
void debugDraw()
```
Visualize grid and path for debugging

### Helper Functions
```cpp
bool isWalkable(int pixelX, int pixelY)
```
Check if pixel position is walkable (R=255 in navMap)
```cpp
GridCell getCell(int gridX, int gridY)
```
Get grid cell at coordinates
```cpp
void pixelToGrid(float pixelX, float pixelY, int& gridX, int& gridY)
```
Convert pixel coordinates to grid coordinates
```cpp
Vector2 gridToPixel(int gridX, int gridY)
```
Convert grid coordinates to pixel coordinates (returns center of cell)
```cpp
int calculateHeuristic(int x1, int y1, int x2, int y2)
```
Calculate estimated cost from position to goal
```cpp
PathNode* findLowestFCost(std::vector<PathNode*>& nodes)
```
Find node with lowest fCost in list

---

## Integration with Other Systems

### With Game
- Game calls `setScene()` when switching scenes
- Game calls `clearPath()` on scene change
- Game provides reference during init

### With InputManager
- InputManager calls `findPath()` on mouse click
- Passes clicked position as goal
- Start position currently hardcoded (will be player position)

### With ScreenManager
- ScreenManager calls `debugDraw()` when debug mode enabled (F1)
- Visualizes grid cells (green=walkable, red=blocked)
- Draws path (yellow lines, orange waypoints)

### With Scene
- Reads navMap Image from Scene
- navMap must be same resolution as screen (1920×1080)
- Red channel (R=255) marks walkable areas

---

## Debug Visualization

**Grid Display:**
- Green circles (5px radius): Walkable cells
- Red circles (5px radius): Blocked cells
- Drawn at grid cell centers

**Path Display:**
- Yellow lines: Connect waypoints in sequence
- Orange circles (8px radius): Waypoint positions
- Only drawn when path exists

**Toggle:** F1 key enables/disables debug mode

---

## Performance Characteristics

**Grid Building:**
- O(width × height) - builds once per scene load
- ~858 cells for 1920×1080 with 25px cells

**Pathfinding:**
- Time: O(n log n) average case with A*
- Space: O(n) for open/closed lists
- Iteration limit: 10,000 to prevent infinite loops
- Typical path length: 20-50 waypoints

**Memory:**
- Grid: ~3.4KB (858 cells × 4 bytes each)
- PathNodes: Allocated during search, cleaned up after
- Current path: Persistent until cleared

---

## Configuration

**Grid Cell Size:**
```cpp
int gridCellSize = 25;  // pixels
```
Smaller = more accurate but slower pathfinding
Larger = faster but less precise paths

**Movement Costs:**
```cpp
Straight: 10
Diagonal: 14  // Approximates √2 ≈ 1.414
```

**Safety Limits:**
```cpp
MAX_ITERATIONS = 10000  // Prevent infinite loops
```

---

## Known Limitations

- **No path smoothing:** Returns grid-aligned waypoints, could be smoothed for more natural movement
- **Fixed grid size:** Cannot adapt to different scenes or resolutions dynamically
- **Linear openList search:** Finding lowest fCost is O(n), could use priority_queue for O(log n)
- **Memory allocation:** Creates/deletes many PathNodes during search, could use object pool

---

## Future Improvements

**Optimization:**
- Use `std::priority_queue` for openList (faster lowest fCost lookup)
- Path smoothing (string pulling, Catmull-Rom splines)
- Jump Point Search for grid optimization
- Object pool for PathNode allocation

**Features:**
- Dynamic obstacles (moving NPCs)
- Multiple cost types (water slower than ground)
- Path caching for repeated queries
- Hierarchical pathfinding for large maps

---

## Example Usage
```cpp
// In InputManager when player clicks
Vector2 playerPos = {50, 400};
Vector2 clickPos = GetMousePosition();

// Find path
std::vector<Vector2> path = navigationManager->findPath(playerPos, clickPos);

if (!path.empty()) {
    // Path found - pawn will follow waypoints
    Logger::info("Path found with " + std::to_string(path.size()) + " waypoints");
} else {
    // No path - position unreachable or not walkable
    Logger::warn("Cannot reach clicked position");
}
```

---

## Design Notes

- Navigation is **purely computational** - doesn't move pawns, just calculates paths
- Paths are **stored** until explicitly cleared or recalculated
- Grid is **rebuilt** each time scene changes to match new navMap
- **Diagonal blocking** prevents visually unrealistic movement through corners
- **Cost-based** movement allows future terrain types (mud, water, etc.)