#include "mouseInput.h"

Vector2 MouseInput::GetValidPosition(){

    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
        return GetMousePosition();
    };

    return {-1, -1};

}