#ifndef MOUSEINPUT_H
#define MOUSEINPUT_H

#include "raylib.h" 

class MouseInput{

    public:
        MouseInput();

        Vector2 GetValidPosition(Vector2 mousePosition);

        bool isWalkable(Vector2 pos);

        void DragObject();

        bool isClickWalkable(Vector2 position);
        bool isClickOnObject(Vector2 position);
    private:

};
#endif;