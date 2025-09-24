#include "raylib.h"
#include <vector>

class Player {

    public:
        Player();
        void setTargetPosition(Vector2 newPosition);
        void updatePosition();
        void checkPosition();
        void draw();
        void setPath(std::vector<Vector2> path);
        Vector2 getCurrentPosition();

    private:
        Vector2 currentPosition;
        Vector2 targetPosition;
        float movementSpeed;
        float movementTreshold;
        bool isMoving;
        std::vector<Vector2> waypoints;
        int currentWaypointIndex;


};