#include "player.h"
#include <raymath.h>

Player::Player(){
    currentPosition = {0, 0};
    targetPosition = currentPosition;
    isMoving = false;
    movementSpeed = .75f;
    movementTreshold = movementSpeed * 1.25f;
}

void Player::setTargetPosition(Vector2 newPosition){
    if(Vector2Distance(targetPosition, newPosition) > movementTreshold ){
        targetPosition = newPosition;
        isMoving = true;
    }
};

void Player::updatePosition(){
    if (Vector2Distance(targetPosition, currentPosition) > movementTreshold){
        Vector2 direction = Vector2Normalize(targetPosition - currentPosition);
        Vector2 movement = Vector2Scale(direction, movementSpeed);
        currentPosition = Vector2Add(currentPosition, movement);        
    } else {
        isMoving = false;
    }

};

void Player::checkPosition(){

};

void Player::draw(){
    DrawRectangle(currentPosition.x-10, currentPosition.y-10, 20, 20, RED);
};