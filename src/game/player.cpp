#include <game/player.h>
#include <raymath.h>

Player::Player(){
    currentPosition = {0, 400};
    targetPosition = currentPosition;
    isMoving = false;
    movementSpeed = 3.5f;
    movementTreshold = movementSpeed * 1.25f;
}

void Player::setPath(std::vector<Vector2> path){
    waypoints = path; 
    currentWaypointIndex = 0;  // Start with first waypoint
    if (!waypoints.empty()) {
        isMoving = true;
    }
};

void Player::setTargetPosition(Vector2 newPosition){
    if (newPosition.x == -1){
        return;
    }
    if(Vector2Distance(targetPosition, newPosition) > movementTreshold ){
        targetPosition = newPosition;
        isMoving = true;
    }
};

void Player::updatePosition(){
    if (waypoints.empty() || currentWaypointIndex >= waypoints.size()) {
        isMoving = false;
        return;
    }
    if (Vector2Distance(waypoints[currentWaypointIndex], currentPosition) > movementTreshold){
        Vector2 direction = Vector2Normalize(waypoints[currentWaypointIndex] - currentPosition);
        Vector2 movement = Vector2Scale(direction, movementSpeed);
        currentPosition = Vector2Add(currentPosition, movement);        
    } else {
        currentWaypointIndex++;  // Move to next waypoint
        if (currentWaypointIndex >= waypoints.size()) {
            isMoving = false;  // Reached final waypoint
        }
    }

};

void Player::checkPosition(){

};

void Player::draw(){
    DrawRectangle(currentPosition.x-10, currentPosition.y-10, 20, 20, RED);
};

Vector2 Player::getCurrentPosition(){
    return currentPosition;
}