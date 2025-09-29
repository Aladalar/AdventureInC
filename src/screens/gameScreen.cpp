#include <screens/gameScreen.h>


GameScreen::GameScreen(GameObject& gameObject) 
    : gameObject(gameObject) {
}

GameScreen::~GameScreen() {
}

void GameScreen::update() {
    if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
        gameObject.handleClick(GetMousePosition());
    }
    gameObject.update();
}

void GameScreen::draw() {
    Scene* scene = gameObject.getCurrentScene();
    if (scene != nullptr) {
        DrawTexture(scene->getBackground(), 0, 0, WHITE);
        gameObject.getPlayer().draw();
        gameObject.getNavigation().drawDebugGrid();
        gameObject.getNavigation().drawDebugPath();
        drawDebugTransitions(scene->getMapTranstitions());
    }
}

void GameScreen::onEnter(){
}

void GameScreen::onExit(){
}

void GameScreen::drawDebugTransitions(const std::vector<Scene::MapTransition>& transitions) {
    for (const Scene::MapTransition& transition : transitions) {
        // Draw trigger zone as a rectangle
        DrawRectangle(
            transition.position.x - 50, 
            transition.position.y - transition.transitionHeight / 2,
            100,
            transition.transitionHeight,
            ColorAlpha(YELLOW, 0.3f)
        );
        // Draw center point
        DrawCircle(transition.position.x, transition.position.y, 10, ORANGE);
    }
}