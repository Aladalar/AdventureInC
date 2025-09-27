#include <game/mouseInput.h>

MouseInput::MouseInput(){
}

Image collisionMap = LoadImage("assets/data/collision/test-collision.png");

Vector2 MouseInput::GetValidPosition(Vector2 mousePosition){
    if (isWalkable(mousePosition)){
        return mousePosition;
    }
    return {-1,-1};
}

bool MouseInput::isWalkable(Vector2 pos) {
    return ColorIsEqual(GetImageColor(collisionMap, pos.x, pos.y), WHITE);
}