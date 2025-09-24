
#include "raylib.h" 

class MouseInput{

    public:
        Vector2 GetValidPosition();
        void DragObject();

        bool isClickWalkable(Vector2 position);
        bool isClickOnObject(Vector2 position);

};