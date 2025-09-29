#include "game/mouseInput.h"
#include "raylib.h"

MouseInput::MouseInput() {
    // Empty constructor - no initialization needed
}

Vector2 MouseInput::GetValidPosition(Vector2 mousePosition, const Image& map){
    if (isWalkable(mousePosition, map)){
        return mousePosition;
    }
    return {-1,-1};
}

bool MouseInput::isWalkable(Vector2 pos,const Image& map) {
    return ColorIsEqual(GetImageColor(map, pos.x, pos.y), WHITE);
} 
