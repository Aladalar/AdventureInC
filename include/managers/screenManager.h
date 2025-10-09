#ifndef SCREEN_M_H
#define SCREEN_M_H

#include "world/scene.h"

class ScreenManager
{
public:
    ScreenManager();
    ~ScreenManager();
    void init();
    void update();

    //Scene managment
    void setScene(Scene* scene);
    void clearScene();

    //Common render
    void draw();
    void drawDebug();

    //UI Render
    void setDebugMode(bool enabled);
    void showMenu(bool show);
    void showDialogue(/*string text*/);
    void hideDialogue();

private:
    void drawBackground();
    void drawFrontground();
    void drawItems();
    void drawPawns();
    void drawUI();
    void drawDialogueBox();
    void drawMenu();
    void drawTransitionOverlay();
    void drawDebugOverlays();

    Scene* activeScene;
protected:
    /* 
    SceneObject* currentScene;
    PawnManager* pawnManager;     
    DialogueManager* dialogueManager;
    GameObject* gameObject;  
    ...
    */

    bool debugMode;
    bool menuVisible;
    bool dialogueVisible;
    //string currentDialogueText;
};

#endif 