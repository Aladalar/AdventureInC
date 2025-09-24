#include "mouseInput.h"

MouseInput::MouseInput(){
}

Vector2 MouseInput::GetValidPosition(Vector2 mousePosition){
    if (isWalkable(mousePosition)){
        return mousePosition;
    }
    return {-1,-1};
}

bool MouseInput::isWalkable(Vector2 pos) {
    // White rectangle from (0,400) to (800,600)
    return (pos.x >= 0 && pos.x <= 800 && pos.y >= 400 && pos.y <= 600);
}