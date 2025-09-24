#include "raylib.h"

class Player {

    public:
        Player();
        void setTargetPosition(Vector2 newPosition);
        void updatePosition();
        void checkPosition();
        void draw();
    private:
        Vector2 currentPosition;
        Vector2 targetPosition;
        float movementSpeed;
        float movementTreshold;
        bool isMoving;

};